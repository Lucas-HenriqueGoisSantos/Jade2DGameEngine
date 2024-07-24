#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem: puclic System {

puclic:
    CollisionSystem() {

        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    bool CheckAABBCollision( double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH ) {

        return (
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY
        );
    }

    Update() {

        auto entities = GetSystemEntities();

        for ( auto i: entities.begin(); i != entities.end(); i++ ) {

            Entity a = *i;
            auto aTransform = a.GetComponent<TransformComponent>();
            auto aCollider = a.GetComponent<BoxColliderComponent>();

            for ( auto j = i; j != entities.end(); j++ ) {

                Entity b = *j;

                if ( a == b ) { continue; }

                auto bTransform = b.GetComponent<TransformComponent>();
                auto bCollider = b.GetComponent<BoxColliderComponent>();

                bool collisionHappened = CheckAABBCollision( 
                    aTransform.position.x,
                    aTransform.position.y,
                    aTransform.width,
                    aTransform.height,

                    bTransform.position.x,
                    bTransform.position.y,
                    bTransform.width,
                    bTransform.height
                );

                if ( collisionHappened ) {

                    Logger::Log( "Entity " + std::to_string( a.GetId() ) + " is colliding with entity " + std::to_string( b.GetId() ) );
                }
            }
        }
    }
}


#endif