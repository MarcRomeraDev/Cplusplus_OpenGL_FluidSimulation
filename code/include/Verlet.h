#pragma once
#include "Mesh.h"
#include "Solver.h"

class Verlet : public Solver
{
public:
	Verlet();
	Verlet(glm::vec3, float, float, float, bool);

	void Update(Mesh&, float);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3, float, float);
};