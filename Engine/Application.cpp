#include "lppch.h"
#include "Application.h"

Application::Application(string name)
{
	WindowInfo info = WindowInfo();
	info.name = name.c_str();
	info.flags = SDL_WINDOW_RESIZABLE;
	info.resolution.width = 400;
	info.resolution.height = 400;

	window = new Window(&info);
}

void Application::Run(Update update)
{
	while(!window->ShouldClose())
	{
		window->ProcessEvents();
		update();

	}
}

Application::~Application()
{
	free(window);
}

LP_Extern {

	LP_Export Application* Application_create(string name)
	{
		return new Application(name);
	}

	LP_Export void Application_destroy(Application* app)
	{
		free(app);
	}

	LP_Export void Application_run(Application* app, Update update)
	{
		app->Run(update);
	}
}