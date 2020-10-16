#ifndef PLAY_ON_HIT_H
#define PLAY_ON_HIT_H
#include "../Rendering/3D/GameObject.h"
#include "../Audio/AudioSource.h"

class PlayOnHit : public Component {

	bool wasHitLastFrame;
	AudioSource* source;

public:

	PlayOnHit();
	~PlayOnHit();

	virtual void OnCreate() override;
	virtual void Update(const float&) override;


};

#endif // !PLAY_ON_HIT_H