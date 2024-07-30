#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../Logger/Logger.h"
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

		Logger::Log( "The Damage system received an event collision between entities " + std::to_string( event.a.GetId() ) + " and " + std::to_string( event.b.GetId() ) );
		
		event.a.Kill();
		event.b.Kill();
	}

	void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<CollisionEvent>( this, &DamageSystem::onCollision );
	}

	void Update() {

	}
};


#endif // !DAMAGESYSTEM_H
