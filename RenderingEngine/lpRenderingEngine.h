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


LP_Export struct RenderingEngineCreateInfo
{
	int rendererType;
	SDL_Window* window;
};


enum RendererType
{
	OpenGL = 0,
	DirectX12 = 1,
	Vulkan = 2,
	Metal = 3
};

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
	~RenderingFramework();
};

int LP_Export GetRendererType();

std::string LP_Export GetRendereTypeName(int renderer);

LP_Export RenderingFramework* InitializeRendering(RenderingEngineCreateInfo* createInfo);

LP_Export int SwapBuffers(RenderingFramework* renderer);

LP_Export int ClearScreen(RenderingFramework* renderer);
#endif