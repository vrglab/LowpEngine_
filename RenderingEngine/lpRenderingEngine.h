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

#include "CreateGlResource.h"

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

#include "OpenGLResourceFactory.h"

#include "Dx12RenderinResource.h"

#include "RenderingFramework.h"

#include "Windowing/Resolution.h"

#include "Windowing/WindowingCreateInfo.h"

#include "Windowing/Windowing.h"

#include "RenderingEngineCreateInfo.h"


enum RendererType
{
	OpenGL = 0,
	DirectX12 = 1,
	Vulkan = 2,
	Metal = 3
};

#include "FunctionDefinitions.h"
#endif