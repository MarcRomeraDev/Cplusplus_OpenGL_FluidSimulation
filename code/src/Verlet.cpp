#include "Verlet.h"

Verlet::Verlet() : Solver() {}
Verlet::Verlet(glm::vec3 sphereC, float r, float mass, bool useSphereCollision) : Solver(sphereC, r, mass, useSphereCollision) {}

void Verlet::Update(Mesh& mesh, float dt, float timer) //--> Update del Euler Solver
{
	float liquidDensity = 1.f; //--> Densitat del liquid

	glm::vec3 weight = gravity * sphere.mass; //--> Pes de l'objecte (la gravetat ja ve passada en negatiu)
	Fbuoyancy = liquidDensity * 9.8f * GetVolumUnderLiquid(mesh.contactPos.y) * glm::vec3(0, 1, 0); //--> Càlcul de la força de buoyancy
	sphere.c = sphere.c + dt * (weight + Fbuoyancy); //--> Actualitzacio de posició amb forces de Euler
}

float Verlet::GetVolumUnderLiquid(float planeHeight)
{
	float volumeUnderLiquid = 0;

	if ((sphere.c.y - sphere.r) < planeHeight) // if the spheres is at least partly underwater
	{
		float relativeHeight = planeHeight - (sphere.c.y - sphere.r);
		if (relativeHeight > sphere.r * 2)
		{
			relativeHeight = sphere.r * 2;
		}

		// Resultat de la integral per obtenir el volum submergit
		volumeUnderLiquid = ((3.14f * glm::pow(relativeHeight, 2.f)) / 3.f) * ((sphere.r * 3.f) - relativeHeight);
	}

	return volumeUnderLiquid;
}