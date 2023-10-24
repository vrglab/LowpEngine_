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
#include <EngineCommons/LowpCommons.h>
#include "Windowing/WindowingCreateInfo.h"
#include "RenderingFramework.h"

LP_Export class Windowing
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