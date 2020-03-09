#include "LightSource.h"


LightSource::LightSource()
	: position(0.0f), ambient(0.0f), diffuse(0.0f), color(0.0f) { }

LightSource::LightSource(const vec3& position_, const float& ambient_, const float& diffuse_, const vec3& color_)
	: position(position_), ambient(ambient_), diffuse(diffuse_), color(color_) { }

LightSource::~LightSource() { }
