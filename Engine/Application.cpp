#include "lppch.h"
#include "Application.h"

Application::Application()
{
	WindowInfo info = WindowInfo();
	info.name = "Example";
	info.flags = SDL_WINDOW_RESIZABLE;
	info.resolution.width = 100;
	info.resolution.height = 100;

	window = new Window(&info);
}

Application::~Application()
{
	free(window);
}
