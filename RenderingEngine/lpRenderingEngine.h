/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef lpEngine_Rendering
#define lpEngine_Rendering
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <LowpCommons.h>

#ifdef _WIN32
#include <Windows.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#endif

#ifdef min
#undef min
#endif

#include <gl/glew.h>
#include <glm/fwd.hpp>
#include <vulkan/vulkan.h>

#ifdef __APPLE__ 
#include <metal/Metal/Metal.hpp>
#include <metal/QuartzCore/QuartzCore.hpp>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>
#include<stb_image.h>


struct CreatedGlResource
{
public:
	GLuint glHandle;
	int Type = 0;
};

enum ResourceType
{
	ShaderProgram = 0,
	Texture = 1,
	Buffer = 2,
	Shader = 3,
	FrameBuffer = 4,
	RenderBuffer = 5,
	VertexArray = 6,
	VertexBuffer = 7,
	IndexBuffer = 8
};

class OpenGLResourceFactory
{
public:
	~OpenGLResourceFactory();

	GLuint CreateVertexBuffer();
	GLuint CreateIndexBuffer();
	GLuint CreateVertexArray();
	GLuint CreateTexture(const char* imagePath);
	GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	GLuint CreateFrameBuffer();
	GLuint CreateBuffer();
	GLuint CreateRenderBuffer(int width, int height);
	void SetUniformMat4(GLuint program, const char* name, const glm::mat4& matrix);
	void BindVertexArray(GLuint vao);
	void BindVertexBuffer(GLuint vbo, GLuint vao, GLuint attributeIndex, int size, int stride, int offset);
	void BindIndexBuffer(GLuint ibo);
	void UseProgram(GLuint program);
	void ClearScreen(float r, float g, float b, float a);
	void SetViewport(int x, int y, int width, int height);
	void BindTexture(GLenum target, GLuint texture);
	void BindFrameBuffer(GLenum target, GLuint framebuffer);

private:
	GLuint CompileShader(GLenum shaderType, const char* source);
	std::list<CreatedGlResource> createdResources = std::list<CreatedGlResource>();
};

#ifdef __d3d12_h__
LP_Export struct Dx12RenderingResources
{
	ID3D12Resource* renderTarget; // This should be your swap chain's buffer
	ID3D12Resource* depthStencilBuffer;

	ID3D12DescriptorHeap* rtvHeap;
	ID3D12DescriptorHeap* dsvHeap;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
};
#endif

class RenderingFramework
{
public:
	void* device = nullptr;
	void* factory = nullptr;
	void* main_swapchain = nullptr;
	void* command_queue = nullptr;
	void* command_allocator = nullptr;
	void* command_list = nullptr;
	void* root_signature = nullptr;
	void* pipeline_stat = nullptr;
	int rendererType;
	SDL_Window* sdl_window;
#ifdef __d3d12_h__
	Dx12RenderingResources* dx12Resources;
#endif
	~RenderingFramework();
};

struct LP_Export Resolution
{
	int width, height;
};

LP_Export struct WindowingCreateInfo
{
	std::string name;
	int flags;
	Resolution* resolution;
};

class LP_Export Windowing
{
private:
	SDL_Renderer* sdl_renderer;
	bool shouldClose = false;

public:
	Windowing(WindowingCreateInfo*);
	~Windowing();
	void ProcessEvents();
	void Open();
	void Close();
	bool ShouldClose();
	RenderingFramework* framework;
	SDL_Window* sdl_window;
	WindowingCreateInfo* info;
};


LP_Export struct RenderingEngineCreateInfo
{
	int rendererType;
	Windowing* window;
};


enum RendererType
{
	OpenGL = 0,
	DirectX12 = 1,
	Vulkan = 2,
	Metal = 3
};

int LP_Export GetRendererType();

std::string LP_Export GetRendereTypeName(int renderer);

LP_Export RenderingFramework* InitializeRendering(RenderingEngineCreateInfo* createInfo);

LP_Export int SwapBuffers(RenderingFramework* renderer);

LP_Export int ClearScreen(RenderingFramework* renderer, float clearColor[4]);
#endif