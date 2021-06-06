#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <ctime>
#include <string>
#include <sstream>
#include <random>

#include "Euler.h"
#include "Mesh.h"
#include "Verlet.h"

bool show_test_window = false;

#pragma region namespaces

namespace LilSpheres {
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius);
}
namespace Capsule {
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
}

namespace ClothMesh {
	extern void updateClothMesh(float* array_data);
	extern const int numCols;
	extern const int numRows;
}

extern bool renderParticles;
extern bool renderSphere;
extern bool renderCapsule;
extern bool renderCloth;

#pragma endregion

#pragma region Variables globals
std::random_device rd;
std::mt19937 gen(rd());
Solver* solver;
Mesh mesh;
std::string t;
float timer = 0;
float resetTimer = 20;
bool autoReset = false;
bool usingVerlet = true;
bool playSimulation = false;
bool useSphereCollision = false;
bool enableParticles = false;
glm::vec3 sphereC;
float r;
float rebound;
float friction;
#pragma endregion

//Funció que reinicialitza i per tant reseteja tots els elements desitjats de la simulació
void ResetSimulation()
{
	timer = 0;
	std::uniform_real_distribution<double> radius(1, 2);
	r = radius(gen);
	std::uniform_real_distribution<double> centerX(-5 + r, 5 - r);
	std::uniform_real_distribution<double> centerY(r, 9.5 - r);
	std::uniform_real_distribution<double> centerZ(-5 + r, 5 - r);
	sphereC = glm::vec3(centerX(gen), centerY(gen), centerZ(gen));
	rebound = solver->reboundCoefficient;
	friction = solver->frictionCoefficient;
	useSphereCollision = solver->useSphereCollision;
	mesh.InitMesh();
	delete solver;
	if (usingVerlet) solver = new Verlet(sphereC, r, rebound, friction, useSphereCollision);
	else solver = new Euler(sphereC, r, rebound, friction, useSphereCollision);
}

//Paràmetres modificables des de l'interfaç
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Checkbox("Play simulation", &playSimulation);
		ImGui::Checkbox("Enable particles", &renderParticles);

		if (ImGui::RadioButton("Euler", (int*)&usingVerlet, 0)) ResetSimulation();
		ImGui::SameLine();
		if (ImGui::RadioButton("Verlet", (int*)&usingVerlet, 1)) ResetSimulation();

		ImGui::DragFloat("Stretch rest length", (float*)&mesh.LStretch, 0.005f, 0.1, 1.f);

		if (ImGui::CollapsingHeader("Solver parameters"))
		{
			ImGui::DragFloat3("Gravity", (float*)&solver->gravity, 0.05f, -9.81f, 9.81f);
		}

		if (ImGui::CollapsingHeader("Collision"))
		{
			ImGui::Checkbox("Use Collision", &mesh.useCollision);
			if (mesh.useCollision)
			{
				ImGui::DragFloat("Elasticidad", &solver->reboundCoefficient, 0.005f, 0.f, 1.f);
				ImGui::DragFloat("Friccion", &solver->frictionCoefficient, 0.005f, 0.f, 1.f);

				ImGui::Checkbox("Use sphere collider", &renderSphere);

				if (renderSphere)
				{
					solver->useSphereCollision = true;
					ImGui::DragFloat3("Shpere Pos", (float*)&solver->sphere.c, 0.05f, -9.8f, 9.8f);
					ImGui::DragFloat("Sphere Radius", &solver->sphere.r, 0.005f, 0.3f, 5.f);
				}
				else
					solver->useSphereCollision = false;
			}
		}

		if (ImGui::CollapsingHeader("Spring parameters"))
		{
			if (ImGui::CollapsingHeader("Spring's constants"))
			{
				ImGui::DragFloat("K stretch", (float*)&mesh.kEStretch, 5.f, 1, 2000.f);
				ImGui::DragFloat("K shear", (float*)&mesh.kEShear, 5.f, 1, 2000.f);
				ImGui::DragFloat("K bending", (float*)&mesh.kEBend, 5.f, 1, 2000.f);
			}

			if (ImGui::CollapsingHeader("Spring's dampings"))
			{
				ImGui::DragFloat("Stretch damping", (float*)&mesh.stretchDamping, 0.5f, 0.f, 100.f);
				ImGui::DragFloat("Shear damping", (float*)&mesh.shearDamping, 0.5f, 0.f, 100.f);
				ImGui::DragFloat("Bend damping", (float*)&mesh.bendDamping, 0.5f, 0.f, 100.f);
			}
		}

		t = "Autoreset simulation: " + std::to_string(resetTimer) + "s";
		ImGui::Checkbox(t.c_str(), &autoReset);

		if (autoReset) ImGui::DragFloat("Autoreset timer", (float*)&resetTimer, 0.05f, 5.f, 20.f);

		if (ImGui::Button("Reset simulation")) ResetSimulation();
	}
	ImGui::End();
}

//Inicialitza la simulació
void PhysicsInit()
{
	renderParticles = false;
	renderCloth = true;
	renderSphere = true;
	mesh = Mesh(ClothMesh::numCols, ClothMesh::numRows, glm::vec3(-2.8, 9.5, 4), 0.5, true);
	solver = new Verlet();
	solver->useSphereCollision = renderSphere;
	LilSpheres::particleCount = mesh.width * mesh.height;
}

//Update de les posicions amb el solver que s'estigui usant, de la mesh i de les partícules/esfera/malla
void PhysicsUpdate(float dt)
{
	if (playSimulation)
	{
		timer += dt;
		for (int i = 0; i < 10; i++)
		{
			mesh.GetSpringForces(solver->gravity);
			solver->Update(mesh, dt / 10);
		}

		if (autoReset && timer >= resetTimer) ResetSimulation();
	}
	ClothMesh::updateClothMesh(&mesh.positions[0].x);
	Sphere::updateSphere(solver->sphere.c, solver->sphere.r);
	LilSpheres::updateParticles(0, mesh.width * mesh.height, &mesh.positions[0].x);
}

void PhysicsCleanup() { 
	delete solver; //-->Cleanup del solver
}