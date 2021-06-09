#include "Solver.h"

Solver::Solver() : gravity(0, -9.81, 0), useSphereCollision(0) {}
Solver::Solver(glm::vec3 spherePos, float sphereRadius, float mass, bool _useSphereCollision) : gravity(0, -9.81, 0), useSphereCollision(_useSphereCollision)
{
	sphere.c = spherePos;
	sphere.r = sphereRadius;
	sphere.mass = mass;	
}