#pragma once
#include "Mesh.h"
#include "Solver.h"

class Verlet : public Solver
{
public:
	Verlet();
	Verlet(glm::vec3, float,float, bool);

	glm::vec3 Fbuoyancy;

	void Update(Mesh&, float, float);

	float GetVolumUnderLiquid(float planeHeight);
};