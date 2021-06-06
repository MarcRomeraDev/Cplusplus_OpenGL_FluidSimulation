#pragma once
#include "Mesh.h"
#include "Solver.h"

class Verlet : public Solver
{
public:
	Verlet();
	Verlet(glm::vec3, float, bool);

	void Update(Mesh&, float);

};