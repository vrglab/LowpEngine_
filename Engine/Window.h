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
	public:
		Window(WindowInfo*);
		~Window();

};

