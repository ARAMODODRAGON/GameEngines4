#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H
#include "../Rendering/3D/GameObject.h"
#include <string>
using std::string;

class AudioSource : public Component {
public:

	AudioSource(const string& soundFile, bool shouldLoop = false, bool is3D = true, bool streamAudio = false);
	~AudioSource();

	virtual void OnCreate() override;
	virtual void Update(const float&) override;

	void PlaySound();
	bool IsPlaying() const;

private:

	string soundFile;
	int32_t channelID;

};

#endif // AUDIO_SOURCE_H