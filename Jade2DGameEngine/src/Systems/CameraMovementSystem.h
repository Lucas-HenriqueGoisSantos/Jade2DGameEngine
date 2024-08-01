#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H


#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL.h>


class CameraMovementSystem: System {

public:
    CameraMovementSystem() {

        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    Update( SDL_Rect& camera) {

        for( auto entity: GetSystemEntities() ) {

            auto transform = entity.GetComponent<TransformComponent>();

            
        }
    }
}


#endif