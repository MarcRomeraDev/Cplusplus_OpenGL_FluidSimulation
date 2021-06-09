#include "Verlet.h"

Verlet::Verlet() : Solver() {}
Verlet::Verlet(glm::vec3 sphereC, float r, bool useSphereCollision) : Solver(sphereC, r, useSphereCollision) {}

void Verlet::Update(Mesh& mesh,float dt ,float timer) //--> Update del Verlet Solver
{
	// Calculate Bouyancy
	float liquidDensity = 1000;
	//float h = mesh.GetHeightInPos(sphere.c, timer);

	glm::vec3 Fbuoyancy = liquidDensity * 9.81f * 3 * glm::vec3(0, 1, 0); //GetVolumUnderLiquid(mesh.GetHeightInPos(sphere.c, timer
	sphere.c = sphere.c + dt * (gravity+ Fbuoyancy);

}

float Verlet::GetVolumUnderLiquid(float planeHeight)
{
	float relativeHeight = sphere.c.y - planeHeight + sphere.r;
	float volumeUnderLiquid = ((3.14f * glm::pow(relativeHeight, 2.f)) / 3.f) * ((sphere.r * 3.f) - relativeHeight);
	return volumeUnderLiquid;
}


	//D = m / v,

	// UPDATE 
	//for (int i = 0; i < mesh.maxParticles; i++)
	//{
	//	iPos = mesh.positions[i];
	//	mesh.positions[i] = mesh.positions[i] + (mesh.positions[i] - mesh.positionsBefore[i]) + mesh.forces[i] * glm::pow(dt, 2.f);

	//	if (glm::distance(iPos, mesh.positions[i]) > (mesh.LStretch * 0.1))
	//		mesh.positions[i] = iPos + glm::normalize(mesh.positions[i] - iPos) * (mesh.LStretch * 0.1f);

	//	mesh.celerities[i] = (mesh.positions[i] - iPos) / dt; //--> Càlcul de la velocitat (sense rebot)

	//	if (mesh.useCollision) //--> Booleana per controlar si es calculen col·lisions en la simulació o no
	//	{
	//		//Collision Sphere
	//		if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r) && useSphereCollision)
	//		{
	//			glm::vec3 colPos = GetCollisionPoint(iPos, mesh.positions[i], sphere.c, sphere.r);
	//			glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
	//			float d = GetDFromPlane(colPos, norm);
	//			ReboundPlane(mesh.positions[i], iPos, mesh.celerities[i], norm, d, dt);
	//		}

	//		//Collision Walls
	//		for (int p = 0; p < 6; p++)
	//		{
	//			if ((glm::dot(box.norms[p], iPos) + box.d[p]) * (glm::dot(box.norms[p], mesh.positions[i]) + box.d[p]) <= 0)
	//				ReboundPlane(mesh.positions[i], iPos, mesh.celerities[i], box.norms[p], box.d[p], dt);
	//		}
	//	}
	
	//	mesh.positionsBefore[i] = iPos;
	//}