#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

///////////////////////////////////////////////////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////////////////////////////////////////////////
// We use a bitset to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
///////////////////////////////////////////////////////////////////////////////////////////////

typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent {
protected:
	static int nextId;
};

// Assigns a unique ids to a component type
template <typename T>
class Component: public BaseComponent {

	static int GetId() {
		static auto id = nextId++;
		return id;
	}

};

class Entity {

private:
	int id;

public:
	Entity( int id ) : id( id ) {};
	int GetId() const;

};

///////////////////////////////////////////////////////////////////////////////////////////////
// System
///////////////////////////////////////////////////////////////////////////////////////////////
// The system preocesses entities that contain a specific signature
///////////////////////////////////////////////////////////////////////////////////////////////
class System {

private:
	Signature componentSignature;
	std::vector<Entity> entities;

public:
	System() = default;
	~System() = default;

	void AddEntityToSystem( Entity entity );
	void RemoveEntityFromSystem( Entity entity );
	std::vector<Entity> GetSystemEntities() const;
	Signature& GetComponentSignature() const;

	template <typename T> void RequireComponent();

};

class Registry {

};


template <typename T>
void System::RequireComponent() {
	const auto componentId = Component<T>::GetId;
	componentSignature.set( componentId );
}

#endif // !ECS_H