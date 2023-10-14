#pragma once

struct LP_Export Resolution
{
	int width, height;
};

struct LP_Export WindowInfo
{
		std::string name;
		Resolution resolution;
		int flags = 0;
};

class LP_Export Window
{
	private:
		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;
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

