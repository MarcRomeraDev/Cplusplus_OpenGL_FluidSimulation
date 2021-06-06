#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>

//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();

bool show_test_window = false;
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		Exemple_GUI();
	}
	
	ImGui::End();
}

void PhysicsInit() {
	Exemple_PhysicsInit();
}

void PhysicsUpdate(float dt) {
	Exemple_PhysicsUpdate(dt);
}

void PhysicsCleanup() {
	Exemple_PhysicsCleanup();
}