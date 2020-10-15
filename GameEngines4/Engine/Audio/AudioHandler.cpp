#include "AudioHandler.h"

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
	FMOD::System_Create(&soundSystem);

	int numdrivers;
	soundSystem->getNumDrivers(&numdrivers);
	if (numdrivers == 0) return false;

	// init the system
	soundSystem->init(10, FMOD_INIT_NORMAL, nullptr);
	FMOD_VECTOR fvPosition = ToFModVector(position);
	FMOD_VECTOR fvVelocity = ToFModVector(velocity);
	FMOD_VECTOR fvForward = ToFModVector(forward);
	FMOD_VECTOR fvUp = ToFModVector(up);
	soundSystem->set3DListenerAttributes(0, &fvPosition, &fvVelocity, &fvForward, &fvUp);

	// success
	return true;
}

void AudioHandler::Update() {
	soundSystem->update();
}

void AudioHandler::OnDestroy() {
	// delete the sounds and channels

	for (auto spair : sounds) {
		 spair.second->release();
	}
	sounds.clear();

	for (auto cpair : channels) {
		cpair.second->stop();
	}
	channels.clear();

	soundSystem->release();
	soundSystem = nullptr;
}

FMOD_VECTOR AudioHandler::ToFModVector(const vec3& glmvec) {
	// init the fvec with the glm values
	FMOD_VECTOR fvec { glmvec.x, glmvec.y, glmvec.z };
	////printf("fvec: %fx, %fy, %fz\n", fvec.x, fvec.y, fvec.z);
	return fvec;
}

void AudioHandler::LoadSound(const string& soundFile, bool shouldLoop, bool is3D, bool streamAudio) {
	if (FMOD::Sound* sound = GetSound(soundFile)) return;

	FMOD_MODE mode = FMOD_DEFAULT;
	if (shouldLoop)		mode |= FMOD_LOOP_NORMAL;
	if (is3D)			mode |= FMOD_3D;
	if (streamAudio)	mode |= FMOD_CREATESTREAM;
	else				mode |= FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* sound = nullptr;
	if (soundSystem->createSound(soundFile.c_str(), mode, nullptr, &sound) != FMOD_OK) return;

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
	soundSystem->playSound(s, nullptr, true, &chan);

	// set the 3d attributes
	FMOD_MODE mode;
	s->getMode(&mode);
	if (mode & FMOD_3D) {
		FMOD_VECTOR fvPosition = ToFModVector(position);
		FMOD_VECTOR fvVelocity = ToFModVector(velocity);
		chan->set3DAttributes(&fvPosition, &fvVelocity);
	}

	// set the volume and then unpause it
	chan->setVolume(volume);
	chan->setPaused(false);

	// add the channel and return the id
	int32_t id = channelCreatedCount++;
	channels.insert(std::make_pair(id, chan));
	return id;
}
