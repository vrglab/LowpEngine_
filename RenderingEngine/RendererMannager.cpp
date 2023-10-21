#include "lprdpch.h"
#include "lpRenderingEngine.h"

int LP_Export GetRendererType()
{
#ifdef _WIN32
	return RendererType::DirectX12;
#elif __APPLE__
	return RendererType::Metal;
#endif
#ifdef __gl_h_
	return RendererType::OpenGL;
#else
	return RendererType::Vulkan;
#endif
}

std::string LP_Export GetRendereTypeName(int renderer)
{
	switch (renderer)
	{
	case 0:
		return "OpenGL";
	case 1:
		return "DirectX12";
	case 2:
		return "Vulkan";
	case 3:
		return "Metal";
	}
}

LP_Export RenderingFramework* InitializeRendering(RenderingEngineCreateInfo* createInfo)
{
	RenderingFramework* framework = new RenderingFramework();
	framework->rendererType = createInfo->rendererType;
	if (createInfo->rendererType == RendererType::OpenGL)
	{
		createInfo->window->info->flags |= SDL_WINDOW_OPENGL;
	}

	createInfo->window->Open();
	framework->sdl_window = createInfo->window->sdl_window;


	if (createInfo->rendererType == RendererType::DirectX12) {
#ifdef __d3d12_h__
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		ID3D12Device* device = nullptr;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};

		CoInitialize(nullptr);
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), &framework->device);
		CreateDXGIFactory1(__uuidof(IDXGIFactory4), &framework->factory);

		swapChainDesc.BufferCount = 2;

		IDXGISwapChain1* swapChain;

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		if (SDL_GetWindowWMInfo(createInfo->window->sdl_window, &wmInfo) == -1) {
			// Handle SDL_GetWindowWMInfo error
			SDL_DestroyWindow(createInfo->window->sdl_window);
			SDL_Quit();
			return nullptr;
		}

		((IDXGIFactory4*)framework->factory)->CreateSwapChainForHwnd((IUnknown*)framework->device, wmInfo.info.win.window, &swapChainDesc, nullptr, nullptr, &swapChain);
		framework->main_swapchain = swapChain;

		device = (ID3D12Device*)framework->device;
		device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), &framework->command_queue);
		device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), &framework->command_allocator);

		device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, (ID3D12CommandAllocator*)framework->command_allocator, nullptr, __uuidof(ID3D12GraphicsCommandList), &framework->command_list);
		((ID3D12GraphicsCommandList*)framework->command_list)->Close();



		std::string vs = "cbuffer Constants{float4x4 WorldViewProjection; } struct VertexInput{ float3 Position : POSITION;  float4 Color : COLOR;}; struct PixelInput{float4 Position : SV_POSITION; float4 Color : COLOR;};PixelInput main(VertexInput input){PixelInput output;output.Position = mul(float4(input.Position, 1.0f), WorldViewProjection);output.Color = input.Color;return output;}";
		std::string ps = "struct PixelInput{float4 Position : SV_POSITION; float4 Color : COLOR; };float4 main(PixelInput input) : SV_TARGET{return input.Color;}";

		ID3DBlob* vsBytecode = nullptr;
		ID3DBlob* psBytecode = nullptr;
		ID3D10Blob* errorMessage = nullptr;

		HRESULT result = D3DCompile(vs.c_str(), vs.length(), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vsBytecode, &errorMessage);
		if (FAILED(result)) {
			if (errorMessage) {
				OutputDebugStringA(static_cast<const char*>(errorMessage->GetBufferPointer()));
				errorMessage->Release();
			}
			// Handle the compilation error
		}

		result = D3DCompile(ps.c_str(), ps.length(), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBytecode, &errorMessage);
		if (FAILED(result)) {
			if (errorMessage) {
				OutputDebugStringA(static_cast<const char*>(errorMessage->GetBufferPointer()));
				errorMessage->Release();
			}
			// Handle the compilation error
		}

		// Define and configure the pipeline state
		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc = {};

		pipelineStateDesc.VS = { vsBytecode->GetBufferPointer(), sizeof(vsBytecode->GetBufferPointer()) };
		pipelineStateDesc.PS = { psBytecode->GetBufferPointer(), sizeof(psBytecode->GetBufferPointer()) };
		D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		pipelineStateDesc.InputLayout = { inputLayout, _countof(inputLayout) };
		device->CreateGraphicsPipelineState(&pipelineStateDesc, __uuidof(ID3D12PipelineState), &framework->pipeline_stat);


		D3D12_ROOT_PARAMETER rootParameters[1];
		rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameters[0].Descriptor.ShaderRegister = 0; // Register in the shader
		rootParameters[0].Descriptor.RegisterSpace = 0;  // Register space in the shader
		rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX; // Shader stage visibility

		// Create a root signature
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.NumParameters = 1;
		rootSignatureDesc.pParameters = rootParameters;
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* signature;
		ID3DBlob* error;
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
		device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), __uuidof(ID3D12RootSignature), &framework->root_signature);

		framework->dx12Resources = new Dx12RenderingResources();


		// Define the descriptor heap for RTVs
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = 1; // Specify the number of RTVs you need
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		ID3D12DescriptorHeap* rtvHeap;
		HRESULT hr = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
		if (FAILED(hr)) {
			// Handle error
		}
		framework->dx12Resources->rtvHeap = rtvHeap;

		// Define the descriptor heap for DSVs
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
		dsvHeapDesc.NumDescriptors = 1; // Typically, you have only one DSV
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		ID3D12DescriptorHeap* dsvHeap;
		hr = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
		if (FAILED(hr)) {
			// Handle error
		}
		framework->dx12Resources->dsvHeap = dsvHeap;

		// Create RTV for the swap chain buffer
		framework->dx12Resources->rtvHandle = framework->dx12Resources->rtvHeap->GetCPUDescriptorHandleForHeapStart();
		device->CreateRenderTargetView(framework->dx12Resources->renderTarget, nullptr, framework->dx12Resources->rtvHandle);

		// Create DSV for the depth stencil buffer
		framework->dx12Resources->dsvHandle = framework->dx12Resources->dsvHeap->GetCPUDescriptorHandleForHeapStart();
		device->CreateDepthStencilView(framework->dx12Resources->depthStencilBuffer, nullptr, framework->dx12Resources->dsvHandle);


		signature->Release();
#endif
	}

	if (createInfo->rendererType == RendererType::OpenGL) {
		if (!glewInit())
		{
			return nullptr;
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GLContext context = SDL_GL_CreateContext(createInfo->window->sdl_window);
		if(context == nullptr)
		{
			std::cout << SDL_GetError() << std::endl;
			return nullptr;
		}
		SDL_GL_MakeCurrent(createInfo->window->sdl_window, context);
		framework->device = context;
		framework->factory = new OpenGLResourceFactory();
	}

	if (createInfo->rendererType == RendererType::Vulkan) {
		VkInstanceCreateInfo vk_createInfo = {};
		VkInstance instance;
		VkDevice vkdevice;
		VkDeviceCreateInfo deviceInfo = {};
		uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
		uint32_t presentQueueFamilyIndex = UINT32_MAX;
		uint32_t queueFamilyCount = 0;


		VkApplicationInfo vulkan_app_info = {};
		vulkan_app_info.pEngineName = "LowpEngine";
		vulkan_app_info.engineVersion = 1.0;

		vk_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		vk_createInfo.pApplicationInfo = &vulkan_app_info;

		if (vkCreateInstance(&vk_createInfo, nullptr, &instance) != VK_SUCCESS) {
			// Handle instance creation failure
		}
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0) {
			// Handle no available GPUs
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		vkCreateDevice(devices[0], &deviceInfo, nullptr, &vkdevice);
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		framework->device = vkdevice;

		vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queueFamilyCount, queueFamilies.data());

		for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilies.size()); i++) {
			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				graphicsQueueFamilyIndex = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(devices[0], i, 0, &presentSupport);

			if (presentSupport) {
				presentQueueFamilyIndex = i;
			}

			if (graphicsQueueFamilyIndex != UINT32_MAX && presentQueueFamilyIndex != UINT32_MAX) {
				break;
			}
		}

		if (graphicsQueueFamilyIndex == UINT32_MAX || presentQueueFamilyIndex == UINT32_MAX) {
			// Handle the case where suitable queue families were not found
		}

		// Retrieve the graphics queue and presentation queue.
		VkQueue graphicsQueue;
		vkGetDeviceQueue(vkdevice, graphicsQueueFamilyIndex, 0, &graphicsQueue);
		VkQueue presentQueue;
		vkGetDeviceQueue(vkdevice, presentQueueFamilyIndex, 0, &presentQueue);
		framework->command_list = graphicsQueue;
		framework->command_queue = presentQueue;
	}

	if (createInfo->rendererType == RendererType::Metal) {
#ifdef __APPLE__ 
		id<MTLDevice> device = NULL;
		device = MTLCreateSystemDefaultDevice();
		if (!device) {
			return nullptr;
		}
		framework->device = (void*)&device
#endif
	}
	return framework;
}

LP_Export int SwapBuffers(RenderingFramework* renderer)
{
	if (renderer->rendererType == RendererType::OpenGL)
	{
		SDL_GL_SwapWindow(renderer->sdl_window);
	}

#ifdef __d3d12_h__
	if (renderer->rendererType == RendererType::DirectX12)
	{
		((ID3D12GraphicsCommandList*)renderer->command_list)->Close();
		ID3D12CommandList* ppCommandLists[] = { ((ID3D12GraphicsCommandList*)renderer->command_list) };
		((ID3D12CommandQueue*)renderer->command_queue)->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
		((IDXGISwapChain1*)renderer->main_swapchain)->Present(0,0);
	}
#endif
	
	return LowpResultCodes::Success;
}

LP_Export int ClearScreen(RenderingFramework* renderer, float clearColor[4])
{
	if(renderer->rendererType == RendererType::OpenGL)
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

#ifdef __d3d12_h__
	if (renderer->rendererType == RendererType::DirectX12)
	{
		((ID3D12GraphicsCommandList*)renderer->command_list)->Reset(((ID3D12CommandAllocator*)renderer->command_allocator), ((ID3D12PipelineState*)renderer->pipeline_stat));
		((ID3D12GraphicsCommandList*)renderer->command_list)->SetPipelineState(((ID3D12PipelineState*)renderer->pipeline_stat));
		((ID3D12GraphicsCommandList*)renderer->command_list)->SetGraphicsRootSignature(((ID3D12RootSignature*)renderer->root_signature));
		((ID3D12GraphicsCommandList*)renderer->command_list)->OMSetRenderTargets(1, &renderer->dx12Resources->rtvHandle, false, &renderer->dx12Resources->dsvHandle);
		((ID3D12GraphicsCommandList*)renderer->command_list)->ClearRenderTargetView(renderer->dx12Resources->rtvHandle, clearColor, 0, nullptr);
		((ID3D12GraphicsCommandList*)renderer->command_list)->ClearDepthStencilView(renderer->dx12Resources->dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	}
#endif

	return LowpResultCodes::Success;
}