#pragma once
#include "Window.h"

class Application
{
	private:
		Window* window;

	public:
		Application();
		void Run();
		~Application();
};

