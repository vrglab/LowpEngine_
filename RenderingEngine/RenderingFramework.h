/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
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