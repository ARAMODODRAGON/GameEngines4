#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int numOfParticles_, std::string texture_, std::string shaderProgram_)
{
	textureID = TextureHandler::GetSingleton()->GetTexture(texture_);
	shaderID = ShaderHandler::GetSingleton()->GetShader(shaderProgram_);

	if (textureID == 0 ) {
		DEBUG_ERROR("Texture not found");
		return;
	}

	if (shaderID == 0) {
		DEBUG_ERROR("Shader not found");
		return;
	}

	particles.reserve(numOfParticles_);

	for (int i = 0; i < numOfParticles_; ++i) {
		auto& p = new Particle(shaderID, textureID);
		particles.push_back(p);
	}


}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Update()
{
}

void ParticleEmitter::Render()
{
}

void ParticleEmitter::Ramdomize()
{
	// radomize particle velocity 
	float tmpX = glm::linearRand(0, 10);
	float tmpY = glm::linearRand(0, 10);
	
	
}
