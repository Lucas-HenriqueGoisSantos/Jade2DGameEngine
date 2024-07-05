#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem : public System {
public:
	MovementSystem() {
		// RequiredComponent<TransformComponent>();
		// RequiredComponent<VelocityComponent>();
	}
	void Update() {
	/*	for ( auto entity : GetEntities() ) {

		}*/
	}
};

#endif // !MOVEMENTSYSTEM_H