#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem: public System {

    public:
        CollisionSystem() {

            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }
        

        void Update( std::unique_ptr<EventBus>& eventBus ) {

            auto entities = GetSystemEntities();

            // Loop all the entities that the system is interested in
            for ( auto i = entities.begin(); i != entities.end(); i++ ) {

                Entity a = *i;
                auto aTransform = a.GetComponent<TransformComponent>();
                auto aCollider = a.GetComponent<BoxColliderComponent>();

                // Loop all the entities that still need to be checked ( to the right of i )
                for ( auto j = i; j != entities.end(); j++ ) {

                    Entity b = *j;

                    // Bypass if we are trying to test the same entity
                    if ( a == b ) { continue; }

                    auto bTransform = b.GetComponent<TransformComponent>();
                    auto bCollider = b.GetComponent<BoxColliderComponent>();
                 
                    // Perform the AABB collision check between entities a and b
                    bool collisionHappened = CheckAABBCollision( 

                        aTransform.position.x + aCollider.offset.x,
                        aTransform.position.y + aCollider.offset.y,
                        aCollider.width * aTransform.scale.x,
                        aCollider.height * aTransform.scale.y,

                        bTransform.position.x + bCollider.offset.x,
                        bTransform.position.y + bCollider.offset.y,
                        bCollider.width * bTransform.scale.x,
                        bCollider.height* bTransform.scale.y
                    );

                    if ( collisionHappened ) {

                        eventBus->EmitEvent<CollisionEvent>( a, b );
                        //Logger::Log( "Entity " + std::to_string( a.GetId() ) + " collided wih entity " + std::to_string( b.GetId() ) );
                    }
                }
            }
        }


        bool CheckAABBCollision( double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH ) {

            return ( 

                aX < bX + bW &&
                aX + aW > bX &&
                aY < bY + bH &&
                aY + aH > bY
            );
        }
};

#endif
