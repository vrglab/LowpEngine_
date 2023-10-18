#include "lpsspch.h"
#include "LpSoundSystem.h"

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo)
{
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) {
		return 0;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return 0;
	}
	return 1;
}
