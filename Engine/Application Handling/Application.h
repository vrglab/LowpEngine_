/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														                          */
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

class LP_Export Application
{
	private:
		Window* window;
		SoundSystem* soundSystem;

	public:
		Application(AppInfo* name);
    /// <summary>
		/// Starts the application main loop
		/// </summary>
		/// <param name="update">The update function</param>
		void Run();
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