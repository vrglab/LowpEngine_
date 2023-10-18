#pragma once

struct LP_Export Resolution
{
	int width, height;
};

class LP_Export Window
{
	private:
		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;
		AppInfo* info;
		bool shouldClose = false;

	public:
		Window(AppInfo*);
		~Window();
		void ProcessEvents();
		void Open();
		void Close();
		bool ShouldClose();

};

