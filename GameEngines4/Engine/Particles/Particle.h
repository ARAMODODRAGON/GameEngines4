#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Camera/Camera.h"


class Particle
{
	GLuint VAO, VBO;
	GLuint shaderProgram, textureID;
	GLuint modelLoc, projLoc, colourLoc, textureLoc;

	vec3 position;
	vec2 velocity;
	vec4 colour;

	std::vector<vec2>planePoints;

	float lifeTime;
	float size;

	

public:

	Particle(GLuint shaderProgram_, GLuint texturID_);
	~Particle();
	void Render(Camera* camera_);

	void SetVelocity(vec2 velocity_) { velocity = velocity_; }
	vec2 GetVelocity() { return velocity; }

private:
	void GenerateBuffers();



	
};
#endif // !PARTICLE_H


