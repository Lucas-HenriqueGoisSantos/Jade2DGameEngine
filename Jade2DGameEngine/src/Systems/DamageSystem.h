#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"


class DamageSystem : public System {

public:
	DamageSystem() {

		RequireComponent<BoxColliderComponent>();
	}

	void Update() {

	}
};


#endif // !DAMAGESYSTEM_H
