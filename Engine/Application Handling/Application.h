/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*  Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                                     */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
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
};

class LP_Export Application
{
	private:
		Window* window;

	public:
		Application(GameInfo* name);
		/// <summary>
		/// Starts the application main loop
		/// </summary>
		/// <param name="update">The update function</param>
		void Run(Update update);
		/// <summary>
		/// Stops the loop so that we can exit the application
		/// </summary>
		void Stop();
		/// <summary>
		/// Initializes all of the required things for a application
		/// </summary>
		void Initialize();
		~Application();
};