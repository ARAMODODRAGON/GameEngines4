#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H
#include <iostream>
#include <glew.h>
#include <vector>
#include "../Graphics/TextureHandler.h"
#include "../Graphics/ShaderHandler.h"
#include "Particle.h"
#include <glm/gtc/random.hpp>
#include "../Rendering/3D/GameObject.h"

class ParticleEmitter : public Component {
public:

	ParticleEmitter(uint32_t numOfParticles_, std::string shaderProgram_);
	~ParticleEmitter() final;

	// events
	virtual void Update(const float& delta) override;
	virtual void Render(Camera* camera) override;

	void Randomize(Particle& p);

private:

	uint32_t VAO;
	uint32_t shaderID;

	uint32_t numOfParticles;
	std::vector<Particle> particles;

};

#endif // !PARTICLE_EMITTER_H