#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H


#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL.h>


class CameraMovementSystem: public System {

public:
    CameraMovementSystem() {

        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update( SDL_Rect& camera ) {
    
        for ( auto entity : GetSystemEntities() ) {

            auto transform = entity.GetComponent<TransformComponent>();

            if ( transform.position.x < Game::mapWidth ) {

                camera.x = transform.position.x;
            }

            if ( transform.position.y < Game::mapHeight ) {

                camera.y = transform.position.y;
            }

        }
    }
};


#endif