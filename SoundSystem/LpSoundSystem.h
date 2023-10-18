/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.                                                     */
/* ======================================================================================== */

#ifndef lpEngine_SoundSystem
#define lpEngine_SoundSystem
#include "LowpCommons.h"

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
};

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system);
LP_Export int UpdateSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system);
LP_Export int CloseSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system);
#endif