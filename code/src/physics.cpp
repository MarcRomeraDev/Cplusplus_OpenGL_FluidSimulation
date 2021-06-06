#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <ctime>
#include <string>
#include <sstream>
#include <random>

#include "Mesh.h"
#include "Verlet.h"

bool show_test_window = false;

#pragma region namespaces

namespace LilSpheres {
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius, float mass);
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
Wave wave(0.5, 5, 0.2, glm::vec3(1, 0, 1));
std::random_device rd;
std::mt19937 gen(rd());
Solver* solver;
Mesh mesh;
std::string t;
float timer = 0;
float resetTimer = 15;
bool autoReset = false;
bool playSimulation = false;
bool useSphereCollision = false;
bool enableParticles = false;
glm::vec3 sphereC;
float r = 1;
float mass = 2;
std::string s;
#pragma endregion

//Funci� que reinicialitza i per tant reseteja tots els elements desitjats de la simulaci�
void ResetSimulation()
{
	timer = 0;
	mesh.waves.clear();
	std::uniform_real_distribution<double> centerX(-5 + r, 5 - r);
	std::uniform_real_distribution<double> centerY(3.5 + r, 9.5 - r);
	std::uniform_real_distribution<double> centerZ(-5 + r, 5 - r);
	sphereC = glm::vec3(centerX(gen), centerY(gen), centerZ(gen));
	useSphereCollision = solver->useSphereCollision;
	mesh.InitMesh();
	delete solver;
	solver = new Verlet(sphereC, r, useSphereCollision);
}

//Par�metres modificables des de l'interfa�
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Checkbox("Play simulation", &playSimulation);
		ImGui::Checkbox("Enable particles", &renderParticles);

		if (ImGui::CollapsingHeader("Mesh Parameters"))
		{
			ImGui::Indent();
			ImGui::NewLine();
			s = "Create Wave";
			if (ImGui::Button(s.c_str())) mesh.waves.push_back(wave); 
			ImGui::NewLine();
			//Informaci� modificable de cada objecte
			for (int i = 0; i < mesh.waves.size(); i++)
			{
				ImGui::PushID(i);
				s = "Wave " + std::to_string(i + 1) + " frequency:";
				ImGui::DragFloat(s.c_str(), &mesh.waves[i].frequency, 0.005f, 0.f, 10.f);

				s = "Wave " + std::to_string(i + 1) + " amplitude:";
				ImGui::DragFloat(s.c_str(), &mesh.waves[i].amplitude, 0.005f, 0.f, 1.f);

				s = "Wave " + std::to_string(i + 1) + " length:";
				ImGui::DragFloat(s.c_str(), &mesh.waves[i].lambda, 0.005f, 0.f, 2.f);

				s = "Wave " + std::to_string(i + 1) + " direction:";
				ImGui::DragFloat3(s.c_str(), (float*)&mesh.waves[i].direction, 0.005f, -1, 1);

				s = "Delete Wave " + std::to_string(i + 1);
				if (ImGui::Button(s.c_str())) mesh.waves.erase(mesh.waves.begin() + i);
				ImGui::NewLine();
				
				ImGui::PopID();
			}

			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader("Solver parameters"))
		{
			ImGui::Indent();

			ImGui::DragFloat3("Gravity", (float*)&solver->gravity, 0.05f, -9.81f, 9.81f);

			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader("Collision"))
		{
			ImGui::Indent();

			ImGui::Checkbox("Use sphere collider", &renderSphere);

			if (renderSphere)
			{
				solver->useSphereCollision = true;
				ImGui::DragFloat3("Shpere Pos", (float*)&solver->sphere.c, 0.05f, -9.8f, 9.8f);
				ImGui::DragFloat("Sphere Radius", &solver->sphere.r, 0.005f, 0.3f, 5.f);
			}
			else solver->useSphereCollision = false;

			ImGui::Unindent();
		}

		t = "Autoreset simulation: " + std::to_string(resetTimer) + "s";
		ImGui::Checkbox(t.c_str(), &autoReset);

		if (autoReset) ImGui::DragFloat("Autoreset timer", (float*)&resetTimer, 0.05f, 5.f, 20.f);

		if (ImGui::Button("Reset simulation")) ResetSimulation();
	}
	ImGui::End();
}

// Inicialitza la simulaci�
void PhysicsInit()
{
	renderParticles = false;
	renderCloth = true;
	renderSphere = true;
	mesh = Mesh(ClothMesh::numCols, ClothMesh::numRows, glm::vec3(-5, 3, 5), 0.770, 0.590, false);
	solver = new Verlet();
	solver->useSphereCollision = renderSphere;
	LilSpheres::particleCount = mesh.width * mesh.height;
}

// Update de les posicions amb el solver que s'estigui usant, de la mesh i de les part�cules/esfera/malla
void PhysicsUpdate(float dt)
{
	if (playSimulation)
	{
		timer += dt;

		if (autoReset && timer >= resetTimer) ResetSimulation();
	}
	for(int i =0; i < mesh.waves.size();i++)
	{
		mesh.waves[i].CalculateWaveNumber();
	}
	mesh.GerstnerWaves(timer);
	ClothMesh::updateClothMesh(&mesh.positions[0].x);
	Sphere::updateSphere(solver->sphere.c, solver->sphere.r, solver->sphere.mass);
	LilSpheres::updateParticles(0, mesh.width * mesh.height, &mesh.positions[0].x);
}

void PhysicsCleanup() {
	delete solver; //-->Cleanup del solver
}