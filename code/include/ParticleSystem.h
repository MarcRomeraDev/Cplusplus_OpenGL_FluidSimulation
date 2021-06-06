#pragma once
#include "Utils.h"

class ParticleSystem
{
public:
	ParticleSystem(int maxParticles = 100);

	void UpdateParticle(int idx, glm::vec3 newPos);
	void UpdateLilSpheres();

	int maxParticles;

	glm::vec3* positions;
	glm::vec3* celerities;
	glm::vec3* positionsBefore;
	glm::vec3* forces;
};