#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H


#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>


class RenderGUISystem: public System {

public:
	RenderGUISystem() = default;

	void Update() {
		
		ImGui::NewFrame();

		// ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
		if ( ImGui::Begin( "Spawn Enemies"/*, NULL, windowFlags*/ ) ) {

			static int enemyXPos = 0;
			ImGui::InputInt( "Enemy X position", &enemyXPos );

			static int enemyYPos = 0;
			ImGui::InputInt( "Enemy Y position", &enemyYPos );
		}
		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render( ImGui::GetDrawData() );
	}
};


#endif // !RENDERGUISYSTEM_H