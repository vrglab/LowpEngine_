#include "lppch.h"
#include "Window.h"

Window::Window(WindowInfo* info)
{
	this->info = info;
}

Window::~Window()
{
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
	free(sdl_window);
	free(info);
}

void Window::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			Close();
		}
	}
}

void Window::Open()
{
	if (SDL_Init(0) != 0)
	{
		return;
	}

	if(info == nullptr)
	{
		return;
	}

	sdl_window = SDL_CreateWindow(info->name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->resolution.width, info->resolution.height, info->flags);

	if (!sdl_window) {
		// Handle window creation error
		SDL_Quit();
		return;
	}
}

void Window::Close()
{
	shouldClose = true;
}

bool Window::ShouldClose()
{
	return shouldClose;
}
