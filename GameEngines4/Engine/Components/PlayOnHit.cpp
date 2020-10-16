#include "PlayOnHit.h"

PlayOnHit::PlayOnHit() : wasHitLastFrame(false), source(nullptr) { }

PlayOnHit::~PlayOnHit() { }

void PlayOnHit::OnCreate() { 
	source = GetObject()->GetComponent<AudioSource>();
	if (source == nullptr) DEBUG_ERROR("No audiosource found! Attach AudioSource before the PlayOnHit component");
}

void PlayOnHit::Update(const float&) { 
	if (source && wasHitLastFrame != GetObject()->GetHit()) {
		DEBUG_INFO("Playing sound!");
		source->PlaySound();
	}
	wasHitLastFrame = GetObject()->GetHit();
}
