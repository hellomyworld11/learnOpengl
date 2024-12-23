#pragma once
#include <vector>

#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"

struct Particle {
	glm::vec2 position, velocity;
	glm::vec4 color;
	float life;
	Particle() :position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) {}
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);

	void update(float dt,
		GameObject& object, 
		unsigned int newParticles, 
		glm::vec2 offset = glm::vec2(0.0f, 0.0f));

	void draw();

private:

	std::vector<Particle> particles_;

	unsigned int amount_;

	Shader shader_;

	Texture2D texture_;

	unsigned int VAO_;

	void init();

	unsigned int firstUnusedParticle();

	void respawnParticle(Particle& particle, GameObject & object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

