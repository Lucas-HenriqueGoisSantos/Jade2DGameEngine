#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../src/ECS/ECS.h"
#include "../src/Components/AnimationComponent.h"
#include "../src/Components/SpriteComponent.h"

class AnimationSystem: public System {

public:

	AnimationSystem() {

		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {

		for ( auto entity: GetSystemEntities() ) {

			auto animation = entity.GetComponent<AnimationComponent>();
			auto sprite = entity.GetComponent<SpriteComponent>();
		}
	}
};


#endif // !ANIMATIONSYSTEM_H
