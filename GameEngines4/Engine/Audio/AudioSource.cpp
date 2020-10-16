#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(const string& soundFile_, bool shouldLoop, bool is3D, bool streamAudio)
	: soundFile(soundFile_), channelID(-1) {
	AudioHandler::GetSingleton()->LoadSound(soundFile, shouldLoop, is3D, streamAudio);
}

AudioSource::~AudioSource() { }

void AudioSource::OnCreate() { }
void AudioSource::Update(const float&) { }

void AudioSource::PlaySound() { 
	channelID = AudioHandler::GetSingleton()->PlaySound(soundFile, GetObject()->GetPosition());
}

bool AudioSource::IsPlaying() const {
	return AudioHandler::GetSingleton()->IsPlaying(channelID);
}
