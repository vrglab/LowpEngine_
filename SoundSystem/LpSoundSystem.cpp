#include "lpsspch.h"
#include "LpSoundSystem.h"

LP_Export int InitSoundSystem(SoundSystemInitInfo initInfo, SoundSystem* ssystem)
{
	ssystem->type = initInfo.be_Type;
	if (ssystem->type == SoundSystemBackendType::Fmod) {

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

	if (ssystem->type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int UpdateSoundSystem(SoundSystem* ssystem)
{
	if (ssystem->type == SoundSystemBackendType::Fmod) {

		return LowpResultCodes::Success;
	}

	if (ssystem->type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int CloseSoundSystem(SoundSystem* ssystem)
{
	if (ssystem->type == SoundSystemBackendType::Fmod) {

		((FMOD::System*)ssystem->system)->release();
		delete(ssystem);
		return LowpResultCodes::Success;
	}

	if (ssystem->type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}
