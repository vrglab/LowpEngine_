#pragma once
#include "Window.h"
typedef void(*Update)();

class Application
{
	private:
		Window* window;

	public:
		Application();
		void Run(Update update);
		~Application();
};

