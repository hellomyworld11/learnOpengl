#include "ParticleGenerator.h"



ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
	:shader_(shader), texture_(texture), amount_(amount)
{
	init();
}

void ParticleGenerator::init()
{
	unsigned int VBO;
	
	float particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
	glBindVertexArray(0);

	for (unsigned int i = 0; i < amount_; i++)
	{
		particles_.push_back(Particle());
	}
}

void ParticleGenerator::update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset /*= glm::vec2(0.0f, 0.0f)*/)
{
	for (unsigned int i = 0; i < newParticles; i++)
	{
		int unusedParticle = firstUnusedParticle();
		respawnParticle(particles_[unusedParticle], object, offset);
	}

	for (unsigned int i = 0; i < amount_; i++)
	{
		Particle &p = particles_[i];
		p.life -= dt;
		if (p.life > 0.0f)
		{
			p.position -= p.velocity * dt;
			p.color.a -= dt*2.5f;
		}
	}

}

void ParticleGenerator::draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader_.use();
	for (Particle particle : particles_)
	{
		if (particle.life > 0.0f)
		{
 			shader_.SetVector2f("offset", particle.position);
			shader_.SetVector4f("color", particle.color);
			texture_.bind();
			glBindVertexArray(VAO_);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
	for (unsigned int i = lastUsedParticle; i < amount_; i++)
	{
		if (particles_[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	for (unsigned int i = 0; i < lastUsedParticle; i++)
	{
		if (particles_[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, GameObject & object, glm::vec2 offset /*= glm::vec2(0.0f, 0.0f)*/)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.position = object.postion_ + random + offset;
	particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = object.velocity_*0.1f;
}
