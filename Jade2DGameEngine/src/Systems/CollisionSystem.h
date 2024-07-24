#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"

class CollisionSystem: puclic System {

puclic:
    CollisionSystem() {
        
        RequireComponent<BoxColliderComponent>();
    }
}


#endif