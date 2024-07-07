#include "ECS.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Entity
int Entity::GetId() const {
	return id;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// System
void System::AddEntityToSystem( Entity entity ) {

}

void System::RemoveEntityFromSystem( Entity entity ) {

}

std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}

Signature& System::GetComponentSignature() const {

}