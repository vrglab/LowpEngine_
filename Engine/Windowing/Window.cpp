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

	SDL_RenderClear(sdl_renderer);

	SDL_RenderPresent(sdl_renderer);
}

void Window::Open()
{

	if (SDL_Init(0) != 0)
	{
		return;
	}

	sdl_window = SDL_CreateWindow(info->name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->resolution.width, info->resolution.height, info->flags);

	if (!sdl_window) {
		// Handle window creation error
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdl_renderer) {
		// Handle renderer creation error
		SDL_DestroyWindow(sdl_window);
		SDL_Quit();
		return;
	}

	std::cout << GetRendererType() << std::endl;
}

void Window::Close()
{
	shouldClose = true;
}

bool Window::ShouldClose()
{
	return shouldClose;
}
