#pragma once
#include "Mesh.h"

class Solver
{
private:
	struct SphereCollider
	{
		glm::vec3 c = { 0.f, 4.f, 0.f };
		float r = 1.f;
	};

	struct CapsuleCollider
	{
		glm::vec3 pos[2] = { glm::vec3(-3.f, 2.f, 0.f), glm::vec3(-3.f, 2.f, 2.f) };
		float r = 1.f;
	};

public:
	Solver();
	Solver(glm::vec3, float, float, float, bool);

	virtual void Update(Mesh&, float) = 0;

	glm::vec3 gravity;
	float reboundCoefficient;
	float frictionCoefficient;
	bool useSphereCollision;
	SphereCollider sphere;
	CapsuleCollider capsule;

protected:
	glm::vec3 iPos;
	glm::vec3 iV;
	glm::vec3 GetCollisionNorm(glm::vec3 collisionPos, glm::vec3 sphereC);
	glm::vec3 GetCollisionPoint(glm::vec3, glm::vec3, glm::vec3, float);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3, float);
	float GetDistanceFromPlane(int, glm::vec3);
	float GetDFromPlane(glm::vec3 collisionPos, glm::vec3 normal);
	bool CheckCollisionSphere(glm::vec3, glm::vec3, float);
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