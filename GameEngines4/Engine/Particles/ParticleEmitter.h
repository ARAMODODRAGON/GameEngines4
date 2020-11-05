#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H
#include <iostream>
#include <glew.h>
#include <vector>
#include "../Graphics/TextureHandler.h"
#include "../Graphics/ShaderHandler.h"
#include "Particle.h"
#include <glm/gtc/random.hpp>



class ParticleEmitter
{ 
	int numOfParticles;

	GLuint shaderID;
	GLuint textureID;

	std::vector<Particle*>particles;



public:
	ParticleEmitter(int numOfParticles_,std::string texture_, std::string shaderProgram_);
	~ParticleEmitter();

	void Update();

	void Render();

	void Ramdomize();
};
#endif // !PARTICLE_EMITTER_H

