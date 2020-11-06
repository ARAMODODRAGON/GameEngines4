#include "ParticleEmitter.h"
#include <random>

float randrange(float min, float max) {
	// (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) gives a value between 0.0f and 1.0f
	// * (max - min) + min will result in a value between min and max
	// rand() isnt the best random generator but it works and this method garuntees any value with my given range
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min) + min;
}

ParticleEmitter::ParticleEmitter(uint32_t numOfParticles_, std::string shaderProgram_)
	: VAO(0), shaderID(0), numOfParticles(numOfParticles_) {

	// load shader
	shaderID = ShaderHandler::GetSingleton()->GetShader(shaderProgram_);
	if (shaderID == 0) {
		DEBUG_ERROR("No shader loaded");
		return;
	}

	// create particles
	particles.reserve(numOfParticles);
	for (int i = 0; i < numOfParticles; ++i) {
		particles.push_back(shaderID); // implicitly construct particle with the given shaderID
		Randomize(particles[i]);
	}

	glCreateVertexArrays(1, &VAO);

}

ParticleEmitter::~ParticleEmitter() {
	glDeleteVertexArrays(1, &VAO);
}

void ParticleEmitter::Update(const float& delta) {
	// update particles
	for (auto& p : particles) {
		// if its ded, restart it
		if (p.GetLifeTime() < 0.0f)
			Randomize(p);
		// update
		p.SetPosition(p.GetPosition() + p.GetVelocity() * delta);
		p.SetLifeTime(p.GetLifeTime() - delta);
	}
}

void ParticleEmitter::Render(Camera* camera) {

	// render all living particles
	//glDisable(GL_DEPTH);
	glUseProgram(shaderID);
	glBindVertexArray(VAO);
	for (auto& p : particles) {
		// check
		//if (p.GetLifeTime() < 0.0f) continue;

		p.Render(camera);
	}
	glBindVertexArray(0);
	glUseProgram(0);
	//glEnable(GL_DEPTH);

}

void ParticleEmitter::Randomize(Particle& p) {

	p.SetLifeTime(randrange(1.0f, 3.0f));
	p.SetSize(randrange(1.0f, 10.0f));
	p.SetPosition(vec3(0.0f));
	p.SetVelocity(glm::sphericalRand(randrange(0.0f, 100.0f)));
	p.SetColour(vec4(randrange(0.0f, 1.0f), randrange(0.0f, 1.0f), randrange(0.0f, 1.0f), randrange(0.0f, 1.0f)));

}