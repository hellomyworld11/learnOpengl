#include "ParticleGenerator.h"



ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
{
	init();
}

void ParticleGenerator::update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset /*= glm::vec2(0.0f, 0.0f)*/)
{

}

void ParticleGenerator::draw()
{

}

void ParticleGenerator::init()
{

}

unsigned int ParticleGenerator::firstUnusedParticle()
{

}

void ParticleGenerator::respawnParticle(Particle& particle, GameObject & object, glm::vec2 offset /*= glm::vec2(0.0f, 0.0f)*/)
{

}
