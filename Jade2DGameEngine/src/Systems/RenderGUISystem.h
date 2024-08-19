#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H


#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>


class RenderGUISystem: public System {

public:
	RenderGUISystem() = default;

	void Update( const std::unique_ptr<Registry>& registry ) {
		
		ImGui::NewFrame();

		// ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
		if ( ImGui::Begin( "Spawn Enemies"/*, NULL, windowFlags*/ ) ) {

			static int enemyXPos = 0;
			static int enemyYPos = 0;

			ImGui::InputInt( "X position", &enemyXPos );
			ImGui::InputInt( "Y position", &enemyYPos );

			if ( ImGui::Button( "Create new enemy" ) ) {

				Entity enemy = registry->CreateEntity();
				enemy.Group( "enemies" );
				enemy.AddComponent<TransformComponent>( glm::vec2( enemyXPos, enemyYPos ), glm::vec2( 1.0, 1.0 ), 0.0 );
				enemy.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
				enemy.AddComponent<SpriteComponent>( "tank-image", 32, 32, 1 );
				enemy.AddComponent<BoxColliderComponent>( 32, 32 );
				enemy.AddComponent<ProjectileEmitterComponent>( glm::vec2( 0.0, 50.0 ), 1000, 1000, 10, false );
				enemy.AddComponent<HealthComponent>( 100 );
			}
		}
		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render( ImGui::GetDrawData() );
	}
};


#endif // !RENDERGUISYSTEM_H