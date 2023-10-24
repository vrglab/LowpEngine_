/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>

#ifdef _WIN32
#include <Windows.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include "Dx12RenderinResource.h"
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