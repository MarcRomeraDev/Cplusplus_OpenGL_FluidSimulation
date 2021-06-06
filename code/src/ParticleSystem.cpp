#include "ParticleSystem.h"
#include <glm/gtx/string_cast.hpp>

namespace LilSpheres {
	extern int firstParticleIdx, particleCount;
	extern const int maxParticles;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

ParticleSystem::ParticleSystem(int _maxParticles) : maxParticles(_maxParticles)
{
	positions = new glm::vec3[maxParticles];
	positionsBefore = new glm::vec3[maxParticles];
	celerities = new glm::vec3[maxParticles];
	forces = new glm::vec3[maxParticles];
}

void ParticleSystem::UpdateParticle(int idx, glm::vec3 newPos) 
{
	positions[idx] = newPos;
}

void ParticleSystem::UpdateLilSpheres()
{
	LilSpheres::firstParticleIdx = 0;
	float* first_float = &(positions[0].x);

	LilSpheres::updateParticles(0, maxParticles, first_float);
}