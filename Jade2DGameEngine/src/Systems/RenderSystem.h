#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Logger/Logger.h"

class RenderSystem : public System {

public:
	RenderSystem() {

        RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update( double deltaTime ) {

		for ( auto entity : GetSystemEntities() ) {

			const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();
		}
	}
};

#endif