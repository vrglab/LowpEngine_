#include "lppch.h"
#include "Application.h"

Application::Application(GameInfo* name)
{
	WindowInfo info = WindowInfo();
	info.name = (string)name->name;
	info.flags = SDL_WINDOW_RESIZABLE;
	info.resolution.width = name->resWidth;
	info.resolution.height = name->resHeight;

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

	LP_Export Application* Application_create(GameInfo* name)
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