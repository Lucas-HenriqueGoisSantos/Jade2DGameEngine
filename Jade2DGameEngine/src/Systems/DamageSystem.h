#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"


class DamageSystem : public System {

public:
	DamageSystem() {

		RequireComponent<BoxColliderComponent>();
	}


	void onCollision( CollisionEvent& event ) {

		// TODO
	}

	void SubscribeToEvent( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<CollisionEvent>( this, &DamageSystem::onCollision );
	}

	void Update() {

	}
};


#endif // !DAMAGESYSTEM_H
