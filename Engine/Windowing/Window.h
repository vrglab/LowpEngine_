#pragma once

struct Resolution
{
	int width, height;
};

struct WindowInfo
{
		std::string name;
		Resolution resolution;
		int flags = 0;
};

class Window
{
	private:
		SDL_Window* sdl_window;
		WindowInfo* info;
		bool shouldClose = false;

	public:
		Window(WindowInfo*);
		~Window();
		void ProcessEvents();
		void Open();
		void Close();
		bool ShouldClose();

};

