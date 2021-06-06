#pragma once
#include "ParticleSystem.h"
#include <vector>

struct Wave {
	float waveNumber;
	float amplitude;
	float frequency;
	glm::vec3 direction;
	float lambda;

	void CalculateWaveNumber(){ waveNumber = (2 * 3.14f) / lambda; }

	Wave() : amplitude(2), frequency(2), direction(glm::vec3(0, 0, 1)), lambda(2)
	{
		CalculateWaveNumber();
	}

	Wave(float _amplitude, float _frequency, float distanceBtwCrests, glm::vec3 waveDirection) : amplitude(_amplitude), frequency(_frequency), direction(waveDirection), lambda(distanceBtwCrests)
	{
		CalculateWaveNumber();
	}


};

class Mesh : public ParticleSystem
{
private:
	int GetIndex(int, int);
	glm::vec3 CalculateForce();

public:
	Mesh();
	Mesh(int _width, int _height, glm::vec3 _initPos, float _LStretchX, float _LStretchY, bool _useCollision);

	void InitMesh();
	void GerstnerWaves(float);

	int width, height;
	float LStretchX, LStretchY;
	glm::vec3 initPos;

	std::vector<Wave> waves;

	bool useCollision;
};