#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Logger/Logger.h"

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

			Logger::Log(
				"Entity id = " +
				std::to_string( entity.GetId() ) +
				" position is now ( " +
				std::to_string( transform.position.x ) +
				", " +
				std::to_string( transform.position.y ) +
				" )" 
			);
		}
	}
};

#endif // !MOVEMENTSYSTEM_H