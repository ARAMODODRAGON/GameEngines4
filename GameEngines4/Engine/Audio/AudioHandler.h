#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H
#include <string>
using std::string;
#include <map>
using std::map;
#include <memory>
#include <fmod\fmod.hpp>
#include <glm\glm.hpp>
using glm::vec3;

class AudioHandler {

	static std::unique_ptr<AudioHandler> inst;
	friend std::default_delete<AudioHandler>;

	AudioHandler();
	~AudioHandler();

	AudioHandler(const AudioHandler&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

public:
	static AudioHandler* GetSingleton() {
		if (inst.get() == nullptr)
			inst.reset(new AudioHandler());
		return inst.get();
	}

	// events

	// inits the audiohandler
	// returns false on failure
	bool Initialize(
		const vec3& position = vec3(0.0f), 
		const vec3& velocity = vec3(0.0f), 
		const vec3& forward = vec3(0.0f, 0.0f, -1.0f), 
		const vec3& up = vec3(0.0f, 1.0f, 0.0f)
	);

	// updates the audiohandler
	void Update();

	// deletes the audiohandler
	void OnDestroy();

private:

	FMOD::System* soundSystem;
	map<string, FMOD::Sound*> sounds;
	map<int32_t, FMOD::Channel*> channels;
	int32_t channelCreatedCount;

	// converts a glm::vec3 to a FMOD_VECTOR
	static FMOD_VECTOR ToFModVector(const vec3& glmvec);

	// loads a sound
	void LoadSound(const string& soundFile, bool shouldLoop, bool is3D, bool streamAudio = false);

	// returns a sound pointer
	FMOD::Sound* GetSound(const string& soundFile);

	// plays a sound and returns the channel ID
	int32_t PlaySound(const string& soundFile, const vec3& position, const vec3& velocity = vec3(0.0f), float volume = 0.0f);

	// updates a channels position and velocity
	void UpdateChannel(int32_t channel_, const vec3& position, const vec3& velocity);

	// returns true if a channel is playing a sound
	bool IsPlaying(int32_t channel_);

};

#endif // !AUDIO_HANDLER_H