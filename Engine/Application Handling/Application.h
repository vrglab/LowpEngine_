#pragma once
typedef void(*Update)();

struct GameInfo
{
	char name[128];
	char version[128];
	char developer[128];
	char publisher[128];
	int resWidth;
	int resHeight;
	int flags;
	SoundSystemInitInfo soundSystem;
};

class LP_Export Application
{
	private:
		Window* window;

	public:
		Application(GameInfo* name);
		void Run(Update update);
		void Stop();
		void Initialize();
		~Application();
};