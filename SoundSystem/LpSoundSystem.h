/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.                                                     */
/* ======================================================================================== */

#ifndef lpEngine_SoundSystem
#define lpEngine_SoundSystem
#include "Macros.h"

enum SoundSystemBackendType {
	Fmod = 0,
	OpenAL = 1
};

LP_Export struct SoundSystemInitInfo {
public:
	int be_Type;
};

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo);
#endif