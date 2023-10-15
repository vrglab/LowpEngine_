#include "lprdpch.h"

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
	RenderingFramework* framwork = new RenderingFramework();
	switch (createInfo->rendererType)
	{
		case RendererType::DirectX12:
#ifdef __d3d12_h__
				CoInitialize(nullptr);
				D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), &framwork->device);
				CreateDXGIFactory1(__uuidof(IDXGIFactory4), &framwork->factory);

				DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
				swapChainDesc.BufferCount = 2;

				IDXGISwapChain1* swapChain;

				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				if (SDL_GetWindowWMInfo(createInfo->window, &wmInfo) == -1) {
					// Handle SDL_GetWindowWMInfo error
					SDL_DestroyWindow(createInfo->window);
					SDL_Quit();
					return nullptr;
				}

				((IDXGIFactory4*)framwork->factory)->CreateSwapChainForHwnd((IUnknown*)framwork->device, wmInfo.info.win.window, &swapChainDesc, nullptr, nullptr, &swapChain);
				framwork->main_swapchain = swapChain;

				ID3D12Device* device = (ID3D12Device*)framwork->device;
				D3D12_COMMAND_QUEUE_DESC queueDesc = {};
				device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), &framwork->command_queue);
				device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), &framwork->command_allocator);

				device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, (ID3D12CommandAllocator*)framwork->command_allocator, nullptr, __uuidof(ID3D12GraphicsCommandList), &framwork->command_list);

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
				device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), __uuidof(ID3D12RootSignature), &framwork->root_signature);

				signature->Release();
#endif
			break;
	}
	return framwork;
}