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


	void OnCollision( CollisionEvent& event ) {

		Entity a = event.a;
		Entity b = event.b;
		
		Logger::Log( "The Damage system received an event collision between entities " + std::to_string( a.GetId() ) + " and " + std::to_string( b.GetId() ) );
		


		//event.a.Kill();
		//event.b.Kill();
	}

	void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<CollisionEvent>( this, &DamageSystem::OnCollision );
	}

	void Update() {

	}
};


#endif // !DAMAGESYSTEM_H
