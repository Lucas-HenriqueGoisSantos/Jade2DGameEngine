#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System {

public:
	MovementSystem() {

		RequiredComponent<TransformComponent>();
		RequiredComponent<RigidBodyComponent>();
	}

	void Update() {

		for ( auto entity : GetSystemEntities() ) {

			auto& transform = entity.GetComponent<TransformComponent>();
			const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += rigidbody.velocity.x;
			transform.position.y += rigidbody.velocity.y;
		}
	}
};

#endif // !MOVEMENTSYSTEM_H