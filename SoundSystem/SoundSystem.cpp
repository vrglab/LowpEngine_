#include "lpsspch.h"
#include "SoundSystem.h"
#include "SoundSystemBackendType.h"

LP_Export int SoundSystem::Init(SoundSystemInitInfo initInfo)
{
	type = initInfo.be_Type;
	if (type == SoundSystemBackendType::Fmod) {

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
		system = fmod_system;
		return LowpResultCodes::Success;
	}

	if (type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int SoundSystem::Update()
{
	if (type == SoundSystemBackendType::Fmod) {

		return LowpResultCodes::Success;
	}

	if (type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}

LP_Export int SoundSystem::Close()
{
	if (type == SoundSystemBackendType::Fmod) {

		((FMOD::System*)system)->release();
		return LowpResultCodes::Success;
	}

	if (type == SoundSystemBackendType::OpenAL) {
		return LowpResultCodes::Success;
	}
	return LowpResultCodes::UnknowError;
}
