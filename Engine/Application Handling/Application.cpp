#include "lppch.h"
#include "Application.h"

Application::Application(GameInfo* G_info)
{
	WindowInfo* info = new WindowInfo();
	info->name = (std::string)G_info->name;
	if(info->name == "")
	{
		info->name = "Fall back name";
	}
	info->flags = G_info->flags;
	info->resolution.width = G_info->resWidth;
	info->resolution.height = G_info->resHeight;

	window = new Window(info);
	SoundSystem* soundSystem = nullptr;
	InitSoundSystem(G_info->soundSystem, soundSystem);
}

void Application::Run(Update update)
{
	while(!window->ShouldClose())
	{
		window->ProcessEvents();
		update();
	}
}

void Application::Stop()
{
	window->Close();
}

void Application::Initialize()
{
	window->Open();
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

	LP_Export void Application_init(Application* app)
	{
		app->Initialize();
	}

	LP_Export void Application_stop(Application* app)
	{
		app->Stop();
	}
}