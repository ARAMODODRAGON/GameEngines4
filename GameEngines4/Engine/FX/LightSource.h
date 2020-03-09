#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/glm.hpp>
using glm::vec3;

class LightSource {

	vec3 position;
	float ambient;
	float diffuse;
	vec3 color;

public:

	LightSource();
	LightSource(const vec3& position, const float& ambient, const float& diffuse, const vec3& color);
	~LightSource();

	/// getters

	vec3 GetPosition() const { return position; }
	float GetAmbient() const { return ambient; }
	float GetDiffuse() const { return diffuse; }
	vec3 GetColor() const { return color; }

	/// setters

	void SetPosition(const vec3& position_) { position = position_; }
	void SetAmbient(const float& ambient_) { ambient = ambient_; }
	void SetDiffuse(const float& diffuse_) { diffuse = diffuse_; }
	void SetColor(const vec3& color_) { color = color_; }

};

#endif // !LIGHTSOURCE_H