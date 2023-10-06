#pragma once
#include "LowpEngine.h"
typedef void(*Update)();

class Application
{
	private:
		Window* window;

	public:
		Application(string name);
		void Run(Update update);
		~Application();
};

