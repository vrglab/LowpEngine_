#include "lpsspch.h"
#include "LpSoundSystem.h"

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system)
{
	system = new SoundSystem();
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) { 

		FMOD::System* fmod_system;
		FMOD_RESULT fmod_result;
		fmod_result = FMOD::System_Create(&fmod_system);
		if (fmod_result != FMOD_OK) {
			return LowpResultCodes::SystemFailure;
		}

		fmod_result = fmod_system->init(32, FMOD_INIT_NORMAL, 0);
		if (fmod_result != FMOD_OK) {
			return LowpResultCodes::SystemFailure;
		}
		system->system = fmod_system;
		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int UpdateSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system)
{
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) {

		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int CloseSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* system)
{
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) {

		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}
