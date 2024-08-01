#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H


#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"


class KeyboardControlSystem : public System {

public:
	KeyboardControlSystem() {

		RequireComponent<KeyboardControlledComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<RigidBodyComponent>();
	}


	void OnKeyPressed( KeyPressedEvent& event ) {

		for ( auto entity: GetSystemEntities() ) {

			const auto keyboardControl = entity.GetComponent<KeyboardControlledComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
		}
	}

	void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<KeyPressedEvent>( this, &KeyboardControlSystem::OnKeyPressed );
	}

	void Update() {

	}
};


#endif // !KEYBOARDCONTROLSYSTEM_H