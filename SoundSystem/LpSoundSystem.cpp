#include "lpsspch.h"
#include "LpSoundSystem.h"

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* ssystem)
{
	ssystem = new SoundSystem();
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
		ssystem->system = fmod_system;
		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int UpdateSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* ssystem)
{
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) {

		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int CloseSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* ssystem)
{
	if (initInfo.be_Type == SoundSystemBackendType::Fmod) {

		((FMOD::System*)ssystem->system)->release();
		delete(ssystem);
		return LowpResultCodes::Success;
	}

	if (initInfo.be_Type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}
