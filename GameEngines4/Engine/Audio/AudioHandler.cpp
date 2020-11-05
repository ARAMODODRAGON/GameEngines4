#include "AudioHandler.h"
#include "../Core/Debug.h"

std::unique_ptr<AudioHandler> AudioHandler::inst = nullptr;

AudioHandler::AudioHandler() : soundSystem(nullptr) {

}

AudioHandler::~AudioHandler() {

}

bool AudioHandler::Initialize(
	const vec3& position,
	const vec3& velocity,
	const vec3& forward,
	const vec3& up
) {
	// create the fmod sound system
	if (FMOD::System_Create(&soundSystem) != FMOD_OK) {
		DEBUG_ERROR("failed to create system");
		return false;
	}

	int numdrivers;
	if (soundSystem->getNumDrivers(&numdrivers) != FMOD_OK) {
		DEBUG_ERROR("failed get num drivers");
		return false;
	}
	if (numdrivers == 0) return false;

	// init the system
	if (soundSystem->init(10, FMOD_INIT_NORMAL, nullptr) != FMOD_OK) {
		DEBUG_ERROR("failed to init system");
		return false;
	}
	// FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED
	FMOD_VECTOR fvPosition = ToFModVector(position);
	FMOD_VECTOR fvVelocity = ToFModVector(velocity);
	FMOD_VECTOR fvForward = ToFModVector(forward);
	FMOD_VECTOR fvUp = ToFModVector(up);
	if (soundSystem->set3DListenerAttributes(0, &fvPosition, &fvVelocity, &fvForward, &fvUp) != FMOD_OK) {
		DEBUG_ERROR("failed to set 3D listener attributes");
		return false;
	}

	// success
	return true;
}

void AudioHandler::Update() {
	soundSystem->update();
}

void AudioHandler::OnDestroy() {
	// delete the sounds and channels

	for (auto cpair : channels) {
		if (cpair.second->stop() != FMOD_OK) {
			DEBUG_ERROR("failed to release channel");
		}
	}
	channels.clear();

	for (auto spair : sounds) {
		if (spair.second->release() != FMOD_OK) {
			DEBUG_ERROR("failed to release sound");
		}
	}
	sounds.clear();

	if (soundSystem->release() != FMOD_OK) {
		DEBUG_ERROR("failed to release system");
	}
	soundSystem = nullptr;
}

FMOD_VECTOR AudioHandler::ToFModVector(const vec3& glmvec) {
	// init the fvec with the glm values
	FMOD_VECTOR fvec { glmvec.x, glmvec.y, glmvec.z };
	////printf("fvec: %fx, %fy, %fz\n", fvec.x, fvec.y, fvec.z);
	return fvec;
}

void AudioHandler::LoadSound(const string& soundFile, bool shouldLoop, bool is3D, bool streamAudio) {
	if (GetSound(soundFile) != nullptr) return;

	FMOD_MODE mode = FMOD_DEFAULT;
	if (shouldLoop)		mode |= FMOD_LOOP_NORMAL;
	if (is3D)			mode |= FMOD_3D;
	if (streamAudio)	mode |= FMOD_CREATESTREAM;
	else				mode |= FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* sound = nullptr;
	if (soundSystem->createSound(soundFile.c_str(), mode, nullptr, &sound) != FMOD_OK) {
		DEBUG_ERROR("failed to create sound");
		return;
	}

	sounds.insert(std::make_pair(soundFile, sound));
}

FMOD::Sound* AudioHandler::GetSound(const string& soundFile) {
	auto sound = sounds.find(soundFile);
	if (sound != sounds.end())
		return sound->second;
	return nullptr;
}

int32_t AudioHandler::PlaySound(const string& soundFile, const vec3& position, const vec3& velocity, float volume) {
	// check if sound exists
	FMOD::Sound* s = GetSound(soundFile);
	if (!s) return -1;

	// channel ID
	FMOD::Channel* chan = nullptr;
	if (soundSystem->playSound(s, nullptr, true, &chan) != FMOD_OK) {
		DEBUG_ERROR("failed to play sound");
		return -1;
	}

	// set the 3d attributes
	FMOD_MODE mode;
	FMOD_RESULT result = s->getMode(&mode);
	if (result == FMOD_OK && mode & FMOD_3D) {
		FMOD_VECTOR fvPosition = ToFModVector(position);
		FMOD_VECTOR fvVelocity = ToFModVector(velocity);
		chan->set3DAttributes(&fvPosition, &fvVelocity);
	} else {
		DEBUG_ERROR("failed to get mode");
		return -1;
	}

	// set the volume and then unpause it
	if (chan->setVolume(volume) != FMOD_OK) {
		DEBUG_ERROR("failed to set volume");
		return -1;
	}
	if (chan->setPaused(false) != FMOD_OK) {
		DEBUG_ERROR("failed to set paused");
		return -1;
	}

	// add the channel and return the id
	int32_t id = channelCreatedCount++;
	channels.insert(std::make_pair(id, chan));
	return id;
}

void AudioHandler::UpdateChannel(int32_t channel_, const vec3& position, const vec3& velocity) {
	auto it = channels.find(channel_);
	if (it == channels.end()) return;

	// set the 3d attributes
	FMOD_VECTOR fvPosition = ToFModVector(position);
	FMOD_VECTOR fvVelocity = ToFModVector(velocity);
	if (it->second->set3DAttributes(&fvPosition, &fvVelocity) != FMOD_OK) {
		DEBUG_ERROR("failed to set channel 3D attributes");
	}
}

bool AudioHandler::IsPlaying(int32_t channel_) {
	auto it = channels.find(channel_);
	if (it == channels.end()) return false;
	bool isPlaying;
	if (it->second->isPlaying(&isPlaying) != FMOD_OK) {
		DEBUG_ERROR("failed to get is playing");
		return false;
	}
	return isPlaying;
}

