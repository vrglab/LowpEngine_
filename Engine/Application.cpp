#include "lppch.h"
#include "Application.h"

Application::Application()
{
	WindowInfo info = WindowInfo();
	info.name = "Example";
	info.flags = SDL_WINDOW_RESIZABLE;
	info.resolution.width = 400;
	info.resolution.height = 400;

	window = new Window(&info);
}

void Application::Run()
{
	while(!window->ShouldClose())
	{
		window->ProcessEvents();

	}
}

Application::~Application()
{
	free(window);
}

LP_Extern {

	LP_Export Application* Application_create()
	{
		return new Application();
	}

	LP_Export void Application_destroy(Application* app)
	{
		free(app);
	}

	LP_Export void Application_run(Application* app)
	{
		app->Run();
	}
}