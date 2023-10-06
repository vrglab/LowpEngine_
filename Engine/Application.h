#pragma once
#include "LowpEngine.h"
typedef void(*Update)();

class Application
{
	private:
		Window* window;

	public:
		Application(const char* name);
		void Run(Update update);
		~Application();
};

