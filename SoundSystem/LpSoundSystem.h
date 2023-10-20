/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */

#ifndef lpEngine_SoundSystem
#define lpEngine_SoundSystem

#ifndef lpEngine_Commons
#include <LowpCommons.h>
#endif

enum SoundSystemBackendType {
	Fmod = 0,
	OpenAL = 1
};

LP_Export struct SoundSystemInitInfo {
public:
	int be_Type;
};

LP_Export struct SoundSystem {
public:
	void* system;
	int type;
};

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system);
LP_Export int UpdateSoundSystem(SoundSystem* system);
LP_Export int CloseSoundSystem(SoundSystem* system);
#endif