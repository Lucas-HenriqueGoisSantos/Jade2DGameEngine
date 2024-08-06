#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"


class DamageSystem : public System {

public:
	DamageSystem() {

		RequireComponent<BoxColliderComponent>();
	}


	void OnCollision( CollisionEvent& event ) {

		Entity a = event.a;
		Entity b = event.b;
		
		Logger::Log( "The Damage system received an event collision between entities " + std::to_string( a.GetId() ) + " and " + std::to_string( b.GetId() ) );
		
		if ( a.BelongsToGroup( "projectiles" ) && b.HasTag( "player" ) ) {
			
			OnProjectileHitsPlayer( a, b );
		}
		if ( b.BelongsToGroup( "projectiles" ) && a.HasTag( "player" ) ) {

			OnProjectileHitsPlayer( b, a );
		}

		if ( a.BelongsToGroup( "projectiles" ) && b.BelongsToGroup( "enemies" ) ) {

		}
		if ( b.BelongsToGroup( "projectiles" ) && a.BelongsToGroup( "enemies" ) ) {

		}

		//event.a.Kill();
		//event.b.Kill();
	}

	void OnProjectileHitsPlayer( Entity projectile, Entity player ) {

		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
	
		if ( projectileComponent.isFriendly ) {

			auto health = player.GetComponent<HealthComponent>();

			health.healthPercentage -= projectileComponent.hitPercentDamage;
		}
	}


	void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<CollisionEvent>( this, &DamageSystem::OnCollision );
	}

	void Update() {

	}
};


#endif // !DAMAGESYSTEM_H
