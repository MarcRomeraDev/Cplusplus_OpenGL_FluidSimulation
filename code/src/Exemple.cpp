#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

/////////Forward declarations
namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

namespace {
	static struct PhysParams {
		float min = 0.f;
		float max = 10.f;
	} p_pars;

	static struct ParticleSystem {
		glm::vec3 *position;
		int numParticles;
	} s_PS;
}

void Exemple_GUI() {
	ImGui::SliderFloat("Min", &p_pars.min, 0.f, 4.f);
	ImGui::SliderFloat("Max", &p_pars.max, 6.f, 10.f);
}

void Exemple_PhysicsInit() {
	s_PS.numParticles = 100;
	s_PS.position = new glm::vec3[s_PS.numParticles];

	extern bool renderParticles; renderParticles = true;
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = s_PS.numParticles;
}

void Exemple_PhysicsUpdate(float dt) {
	for (int i = 0; i < s_PS.numParticles; i++) {
		float x = -5 + p_pars.min + (float)rand() / (RAND_MAX / (p_pars.max - p_pars.min));
		float y =      p_pars.min + (float)rand() / (RAND_MAX / (p_pars.max - p_pars.min));
		float z = -5 + p_pars.min + (float)rand() / (RAND_MAX / (p_pars.max - p_pars.min));

		printf("Creating particle with position %.2f, %.2f, %.2f\n", x, y, z);

		s_PS.position[i] = glm::vec3(x, y, z);
	}

	LilSpheres::updateParticles(0, s_PS.numParticles, &(s_PS.position[0].x));
}

void Exemple_PhysicsCleanup() {
	delete[] s_PS.position;
}

