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

	void Update( const std::unique_ptr<Registry>& registry, SDL_Rect& camera ) {
		
		ImGui::NewFrame();

		// ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
		if ( ImGui::Begin( "Spawn Enemies"/*, NULL, windowFlags*/ ) ) {

			static int posX = 0;
			static int posY = 0;
			static int scaleX = 1;
			static int scaleY = 1;
			static int velX = 0;
			static int velY = 0;
			static int health = 100;
			static float rotation = 0.0;
			static float projAngle = 0.0;
			static float projSpeed = 100.0;
			static int projRepeat = 10;
			static int projDuration = 10;
			const char* sprites[] = { "tank-image", "truck-image" };
			static int seclectedSpriteIndex = 0;


			if ( ImGui::CollapsingHeader( "Sprite", ImGuiTreeNodeFlags_DefaultOpen ) ) {
				
				ImGui::Combo( "Texture ID", &seclectedSpriteIndex, sprites, IM_ARRAYSIZE( sprites ) );
			}
			ImGui::Spacing();

			if ( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) ) {

				ImGui::InputInt( "Position X", &posX );
				ImGui::InputInt( "Position Y", &posY );
				ImGui::SliderInt( "Scale X", &scaleX, 1, 10 );
				ImGui::SliderInt( "Scale Y", &scaleY, 1, 10 );
				ImGui::SliderAngle( "Rotation (deg)", &rotation, 0, 360 );
			}
			ImGui::Spacing();

			if ( ImGui::CollapsingHeader( "Rigid Body", ImGuiTreeNodeFlags_DefaultOpen ) ) {

				ImGui::InputInt( "Velocity X", &velX );
				ImGui::InputInt( "Velocity Y", &velY );
			}
			ImGui::Spacing();

			if ( ImGui::CollapsingHeader( "Projectile Emitter", ImGuiTreeNodeFlags_DefaultOpen ) ) {

				ImGui::SliderAngle( "Angle (deg)", &projAngle, 0, 360 );
				ImGui::SliderFloat( "Speed (px/sec)", &projSpeed, 10, 500 );
				ImGui::InputInt( "Repeat (sec)", &projRepeat );
				ImGui::InputInt( "Duration (sec)", &projDuration );
			}
			ImGui::Spacing();

			if ( ImGui::CollapsingHeader( "Health", ImGuiTreeNodeFlags_DefaultOpen ) ) {

				ImGui::SliderInt( "%", &health, 0, 100 );
			}
			ImGui::Spacing();

			ImGui::Separator();
			ImGui::Spacing();

			if ( ImGui::Button( "Spawn new enemy" ) ) {

				Entity enemy = registry->CreateEntity();
				enemy.Group( "enemies" );
				enemy.AddComponent<TransformComponent>( glm::vec2( posX, posY ), glm::vec2( scaleX, scaleY ), glm::degrees( rotation ) );
				enemy.AddComponent<RigidBodyComponent>( glm::vec2( velX, velY ) );
				enemy.AddComponent<SpriteComponent>( sprites[seclectedSpriteIndex], 32, 32, 2 );
				enemy.AddComponent<BoxColliderComponent>( 32, 32, glm::vec2( 5, 5 ) );
				double projVelX = cos( projAngle ) * projSpeed;
				double projVelY = sin( projAngle ) * projSpeed;
				enemy.AddComponent<ProjectileEmitterComponent>( glm::vec2( projVelX, projVelY ), projRepeat * 1000, projDuration * 1000, 10, false );
				enemy.AddComponent<HealthComponent>( health );

				posX = posY = rotation = projAngle = 0;
				scaleX = scaleY = 1;
				projRepeat = projDuration = 10;
				projSpeed = 100.0;
				health = 100;
			}
		}
		ImGui::End();


		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
		ImGui::SetNextWindowPos( ImVec2( 10, 10 ), ImGuiCond_Always, ImVec2( 0, 0 ) );
		ImGui::SetNextWindowBgAlpha( 0.9f );
		
		if ( ImGui::Begin( "Map Coordinates", NULL, windowFlags ) ) {

			ImGui::Text(
				"Map Coodinates ( x=%.1f, y=%.1f )",
				ImGui::GetIO().MousePos.x + camera.x,
				ImGui::GetIO().MousePos.y + camera.y
			);
		}


		ImGui::Render();
		ImGuiSDL::Render( ImGui::GetDrawData() );
	}
};


#endif // !RENDERGUISYSTEM_H