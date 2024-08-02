#ifndef ECS_H
#define ECS_H

#include "../Logger/Logger.h"
#include <bitset>
#include <set>
#include <deque>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>


const unsigned int MAX_COMPONENTS = 32;

///////////////////////////////////////////////////////////////////////////////////////////////
// Components
///////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------//
// Signature --------------------------------------------------------------------------------//
// We use a bitset to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
//-------------------------------------------------------------------------------------------//
typedef std::bitset<MAX_COMPONENTS> Signature;

// Assigns a unique ids to a component type
struct BaseComponent {

protected:
	static int nextId;
};

template <typename T>
class Component: public BaseComponent {

public:
	static int GetId() {
		static auto id = nextId++;
		return id;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////
// Entities
///////////////////////////////////////////////////////////////////////////////////////////////
class Entity {

private:
	int id;

public:
	Entity( int id ) : id( id ) {};
	Entity( const Entity& entity ) = default;

	int GetId() const;
	void Kill();
	
	Entity& operator =( const Entity& other ) = default;
	bool operator ==( const Entity& other ) const { return id == other.id; }
	bool operator !=( const Entity& other ) const { return id != other.id; }
	bool operator >( const Entity& other ) const { return id > other.id; }
	bool operator <( const Entity& other ) const { return id < other.id; }

	template<typename T, typename ...TArgs> void AddComponent( TArgs&& ...args );
	template<typename T> void RemoveComponent();
	template<typename T> bool HasComponent() const;
	template<typename T> T& GetComponent() const;

	class Registry* registry;
};

///////////////////////////////////////////////////////////////////////////////////////////////
// Systems
///////////////////////////////////////////////////////////////////////////////////////////////
// The system preocesses entities that contain a specific signatures
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
	const Signature& GetComponentSignature() const;

	template <typename T> void RequireComponent();

};

///////////////////////////////////////////////////////////////////////////////////////////////
// Registry
///////////////////////////////////////////////////////////////////////////////////////////////
class IPool {

public:
	virtual ~IPool() {};
};

template <typename T>
class Pool: public IPool {

private:
	std::vector<T> data;

public:
	Pool( int size = 100 ) {
		data.resize( size );
	}
	virtual ~Pool() = default;

	bool IsEmpty() const {
		return data.empty();
	}
	int GetSize() const {
		return static_cast<int>( data.size() );
	}
	void Resize( int n ) {
		data.resize( n );
	}
	void Clear() {
		data.clear();
	}
	void Add( T object ) {
		data.push_back( object );
	}
	void Set( int index, T object ) {
		data[index] = object;
	}
	T& Get( int index ) {
		return static_cast<T&>( data[index] );
	}

	T& operator []( unsigned int index ) {
		data[index];
	}
};

class Registry {

private:
	int numEntities = 0;

	// Each Pool constains all the data for a certain component type
	// [Vector index = component type id]
	// [Pool index = entity id]
	std::vector<std::shared_ptr<IPool>> componentPools;

	// Vector of component signatures per entity, saying which component is turned "on" for which entity
	// [Vector index = entity id]
	std::vector<Signature> entityComponentSignatures;

	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	// Entities to be added in the next Registry Update
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

	// List of free entity ids
	std::deque<int> freeIds;

public:
	Registry() = default;
	
	// Entity management
	Entity CreateEntity();
	void KillEntity( Entity entity );
	void AddEntityToSystems( Entity entity );
	void RemoveEntityFromSystems( Entity entity );

	// Component management
	template<typename T,  typename ...TArgs> void AddComponent( Entity entity, TArgs&& ...args );
	template<typename T> void RemoveComponent( Entity entity );
	template<typename T> bool HasComponent( Entity entity ) const;
	template<typename T> T& GetComponent( Entity entity ) const;

	// System management
	template<typename T, typename ...TArgs> void AddSystem( TArgs&& ...args );
	template<typename T> void RemoveSystem();
	template<typename T> bool HasSystem() const;
	template<typename T> T& GetSystem() const;


	void Update();
};


///////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of templates
///////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void System::RequireComponent() {

	const auto componentId = Component<T>::GetId();
	componentSignature.set( componentId );
}


template<typename T,  typename ...TArgs>
void Registry::AddComponent( Entity entity, TArgs&& ...args ) {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();


	if ( componentId >= componentPools.size() ) {

		componentPools.resize( componentId + 1, nullptr );
	}

	if ( !componentPools[componentId] ) {

		std::shared_ptr<Pool<T>> newComponentPool = std::make_shared<Pool<T>>();
		componentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<T>> componentPool = std::static_pointer_cast<Pool<T>>( componentPools[componentId] );

	if ( entityId >= componentPool->GetSize() ) {
		
		componentPool->Resize( numEntities );
	}

	T newComponent( std::forward<TArgs>( args )... );

	componentPool->Set( entityId, newComponent );

	entityComponentSignatures[entityId].set( componentId );


	Logger::Log( "Component id: " + std::to_string( componentId ) + "was added to entity id:" + std::to_string ( entityId ) );
}


template<typename T>
void Registry::RemoveComponent( Entity entity ) {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set( componentId, false );
}


template<typename T>
bool Registry::HasComponent( Entity entity ) const {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignatures[entityId].test( componentId );
}


template <typename T>
T& Registry::GetComponent(Entity entity) const {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	auto componentPool = std::static_pointer_cast<Pool<T>>( componentPools[componentId] );
	
	return componentPool->Get( entityId );
}

template<typename T, typename ...TArgs>
void Registry::AddSystem( TArgs&& ...args ) {

	std::shared_ptr<T> newSystem = std::make_shared<T>( std::forward<TArgs>( args )... );
	systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}


template<typename T>
void Registry::RemoveSystem() {

	auto system = systems.find( std::type_index( typeid( T ) ) );
	systems.erase( system );
}


template<typename T>
bool Registry::HasSystem() const {

	return systems.find(std::type_index( typeid( T ) ) ) != systems.end();
}


template<typename T>
T& Registry::GetSystem() const {

	auto system = systems.find(std::type_index( typeid( T ) ) );
	return *( std::static_pointer_cast<T>( system->second ) );
}



template<typename T, typename ...TArgs>
void Entity::AddComponent( TArgs&& ...args ) {
	registry->AddComponent<T>( *this, std::forward<TArgs>( args )... );
}


template<typename T>
void Entity::RemoveComponent() {
	registry->RemoveComponent<T>( *this );
}


template<typename T>
bool Entity::HasComponent() const {
	return registry->HasComponent<T>( *this );
}


template<typename T>
T& Entity::GetComponent() const {
	return registry->GetComponent<T>( *this );
}


#endif // !ECS_H