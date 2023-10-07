#include "lppch.h"
#include "Window.h"

Window::Window(WindowInfo* info)
{
	this->info = info;
}

Window::~Window()
{
	shutdown();
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
	cout << "Opening window" << endl;
	if (SDL_Init(0) != 0)
	{
		cout << "sdl init failed" << endl;
		return;
	}

	if(info == nullptr)
	{
		cout << "info is null" << endl;
		return;
	}

	cout << "sdl start creating window" << endl;
	cout << info->name.c_str() << endl;
	cout << info->resolution.width << endl;
	cout << info->resolution.height << endl;
	sdl_window = SDL_CreateWindow(info->name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->resolution.width, info->resolution.height, info->flags);

	cout << "sdl_window made checking if we successeded" << endl;
	if (!sdl_window) {
		// Handle window creation error
		cout << "sdl_window failed its creation phase" << endl;
		SDL_Quit();
		return;
	}


	cout << "bgfx starting" << endl;
	Init init_;

	init_.type = getRendererType();
	init_.resolution = info->resolution;
	bool initiated = init(init_);

	PlatformData platformData;
	bx::memSet(&platformData, 0, sizeof(platformData));
	platformData.nwh = (void*)SDL_GetWindowID(sdl_window);
	platformData.ndt = nullptr;
	platformData.context = nullptr;
	platformData.backBuffer = nullptr;
	platformData.backBufferDS = nullptr;
	setPlatformData(platformData);

	setViewRect(0, 0, 0, info->resolution.width, info->resolution.height);
	setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
}

void Window::Close()
{
	shouldClose = true;
}

bool Window::ShouldClose()
{
	return shouldClose;
}
