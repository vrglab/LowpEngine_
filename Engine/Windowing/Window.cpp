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

	if (!SDL_CreateWindowAndRenderer(info->resolution.width, info->resolution.height, info->flags, &sdl_window, &sdl_renderer)) {
		// Handle window creation error
		SDL_Quit();
		return;
	}

	SDL_SetWindowTitle(sdl_window, info->name.c_str());
}

void Window::Close()
{
	shouldClose = true;
}

bool Window::ShouldClose()
{
	return shouldClose;
}
