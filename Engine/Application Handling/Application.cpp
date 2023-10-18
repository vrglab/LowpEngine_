#include "lppch.h"
#include "Application.h"

Application::Application(AppInfo* G_info)
{
	window = new Window(G_info);

	soundSystem = new SoundSystem();
	InitSoundSystem(G_info->soundSystem, soundSystem);
}

void Application::Run()
{
	while(!window->ShouldClose())
	{
		window->ProcessEvents();



		UpdateSoundSystem(soundSystem);
	}

	CloseSoundSystem(soundSystem);
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

	LP_Export Application* Application_create(AppInfo* name)
	{
		return new Application(name);
	}

	LP_Export void Application_destroy(Application* app)
	{
		free(app);
	}

	LP_Export void Application_run(Application* app)
	{
		app->Run();
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