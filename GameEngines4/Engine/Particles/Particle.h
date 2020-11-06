#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Camera/Camera.h"


class Particle {
public:

	Particle();
	Particle(uint32_t shaderProgram_);
	~Particle();

	// events
	void Render(Camera* camera_);

	// getters & setters
	void SetPosition(const vec3& position_) { position = position_; }
	vec3 GetPosition() { return position; }
	void SetVelocity(const vec3& velocity_) { velocity = velocity_; }
	vec3 GetVelocity() { return velocity; }
	void SetColour(const vec4& colour_) { colour = colour_; }
	vec4 GetColour() { return colour; }
	void  SetLifeTime(float lifeTime_) { lifeTime = lifeTime_; }
	float GetLifeTime() { return lifeTime; }
	void  SetSize(float size_) { size = size_; }
	float GetSize() { return size; }

private:

	void GenerateBuffers(uint32_t shaderProgram_);

	// rendering
	uint32_t positionLoc, colourLoc, sizeLoc, projLoc, viewLoc;

	// properties
	vec3 position;
	vec3 velocity;
	vec4 colour;
	float lifeTime;
	float size;

	std::vector<vec2> planePoints;

};
#endif // !PARTICLE_H


