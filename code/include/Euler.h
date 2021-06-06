#pragma once
#include "Solver.h"

class Euler : public Solver
{
public:
	Euler();
	Euler(glm::vec3, float, float, float, bool);

	void Update(Mesh& mesh, float dt);
};