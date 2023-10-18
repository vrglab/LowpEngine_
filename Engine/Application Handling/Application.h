#pragma once

class LP_Export Application
{
	private:
		Window* window;

	public:
		Application(AppInfo* name);
		void Run();
		void Stop();
		void Initialize();
		~Application();
};