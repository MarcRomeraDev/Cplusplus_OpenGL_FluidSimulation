#pragma once
#include "Mesh.h"

class Solver
{
private:
	struct SphereCollider
	{
		glm::vec3 c = { 0.f, 7.f, 0.f };
		float r = 1.f;
		glm::vec3 vel = { 0,0,0 };
		float mass = 1.f;
	};

public:
	Solver();
	Solver(glm::vec3, float,float, bool);

	virtual void Update(Mesh&, float, float) = 0;

	glm::vec3 gravity;
	bool useSphereCollision;
	SphereCollider sphere;

protected:
	struct BoxCollider
	{
		glm::vec3 pos[2] = { glm::vec3(-5.f, 0.f, -5.f), glm::vec3{5.f, 10.f, 5.f} };
		glm::vec3 norms[6] = {
			glm::vec3(0.f,  1.f,  0.f),
			glm::vec3(1.f,  0.f,  0.f),
			glm::vec3(0.f,  0.f,  1.f),
			glm::vec3(0.f, -1.f,  0.f),
			glm::vec3(-1.f,  0.f,  0.f),
			glm::vec3(0.f,  0.f, -1.f)
		};
		float d[6] = { 0.f, 5.f, 5.f, 10.f, 5.f, 5.f };
	}box;
};