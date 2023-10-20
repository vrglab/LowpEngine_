#include "lppch.h"
#include "LowpEngineCore.h"

Windowing::Windowing(GameInfo* info)
{
	this->info = info;
}

Windowing::~Windowing()
{
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Windowing::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			Close();
		}
	}
}

void Windowing::Open()
{

	if (SDL_Init(0) != 0)
	{
		return;
	}

	sdl_window = SDL_CreateWindow(info->name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->resolution->width, info->resolution->height, info->flags);

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
	RenderingEngineCreateInfo* createInfo = new RenderingEngineCreateInfo();
	createInfo->rendererType = GetRendererType();
	createInfo->window = sdl_window;
	framework = InitializeRendering(createInfo);
}

void Windowing::Close()
{
	shouldClose = true;
}

bool Windowing::ShouldClose()
{
	return shouldClose;
}
