#include "lppch.h"
#include "Window.h"

Window::Window(WindowInfo* info)
{
	if(SDL_Init(0) != 0)
	{
		
	}

	sdl_window = SDL_CreateWindow(info->name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->resolution.width, info->resolution.height, info->flags);
	this->info = info;
}

Window::~Window()
{
	free(sdl_window);
	free(info);
}
