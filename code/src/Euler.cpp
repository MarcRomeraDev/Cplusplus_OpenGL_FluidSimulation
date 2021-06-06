#include "Euler.h"

Euler::Euler() : Solver() {}
Euler::Euler(glm::vec3 sphereC, float r, float rebound, float friction, bool useSphereCollision) : Solver(sphereC, r, rebound, friction, useSphereCollision) {}

void Euler::Update(Mesh& mesh, float dt) // --> Update del Euler Solver
{	
	for (int i = 0; i < mesh.maxParticles; i++)
	{
		iPos = mesh.positions[i];
		iV = mesh.celerities[i];

		mesh.positions[i] = iPos + iV * dt;

		if (glm::distance(iPos, mesh.positions[i]) > (mesh.LStretch * 0.1)) // --> Amb aquest if ens asegurem de que el moviment de particula mai sigui major al 10% de la distancia de repos
			mesh.positions[i] = iPos + glm::normalize(mesh.positions[i] - iPos) * (mesh.LStretch * 0.1f);
		
		mesh.celerities[i] = iV + mesh.forces[i] * dt;

		if (mesh.useCollision) //--> Booleana per controlar si es calculen col·lisions en la simulació o no
		{
			//Collision Sphere
			if (CheckCollisionSphere(mesh.positions[i], sphere.c, sphere.r) && useSphereCollision)
			{
				glm::vec3 colPos = GetCollisionPoint(iPos, mesh.positions[i], sphere.c, sphere.r);
				glm::vec3 norm = GetCollisionNorm(colPos, sphere.c);
				float d = GetDFromPlane(colPos, norm);
				ReboundPlane(mesh.positions[i], mesh.celerities[i], norm, d);
			}

			//Collision Walls
			for (int p = 0; p < 6; p++)
			{
				if ((glm::dot(box.norms[p], iPos) + box.d[p]) * (glm::dot(box.norms[p], mesh.positions[i]) + box.d[p]) <= 0)
					ReboundPlane(mesh.positions[i], mesh.celerities[i], box.norms[p], box.d[p]);
			}
		}
	}
}