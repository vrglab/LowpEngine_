#pragma once

struct WindowInfo
{
	public:
		std::string name;
		Resolution resolution;
		int flags;
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
		void Close();
		bool ShouldClose();

};

