#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <set>
#include <vector>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;
///////////////////////////////////////////////////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////////////////////////////////////////////////
// We use a bitset to keep track of which components an entity has,
// and also helps keep track of which entities a system is interested in.
///////////////////////////////////////////////////////////////////////////////////////////////

typedef std::bitset<MAX_COMPONENTS> Signature;

///////////////////////////////////////////////////////////////////////////////////////////////
// Components
///////////////////////////////////////////////////////////////////////////////////////////////
// Assigns a unique ids to a component type
struct BaseComponent {
protected:
	static int nextId;
};

template <typename T>
class Component: public BaseComponent {

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
	
	Entity& operator =( const Entity& other ) = default;
	bool operator ==( const Entity& other ) const { return id == other.id; }
	bool operator !=( const Entity& other ) const { return id != other.id; }
	bool operator >( const Entity& other ) const { return id > other.id; }
	bool operator <( const Entity& other ) const { return id < other.id; }

};

///////////////////////////////////////////////////////////////////////////////////////////////
// Systems
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
	const Signature& GetComponentSignature() const;

	template <typename T> void RequireComponent();

};

///////////////////////////////////////////////////////////////////////////////////////////////
// Registry
///////////////////////////////////////////////////////////////////////////////////////////////
class IPool {

public:
	virtual ~IPool();
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
		return data.size();
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
	T& Get( int index, T object ) {
		return static_cast<T*>( data[index] );
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
	std::vector<IPool*> componentPools;

	// Vector of component signatures per entity, saying which component is turned "on" for which entity
	// [Vector index = entity id]
	std::vector<Signature> entityComponentSignature;

	std::unordered_map<std::type_index, System*> systems;

	// Entities to be added in the next Registry Update
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

public:
	Registry() = default;
	
	// Entity management
	Entity CreateEntity();
	void AddEntityToSystem( Entity entity );

	// Component management
	template<typename T,  typename ...TArgs> void AddComponent( Entity entity, TArgs&& ...args );
	template<typename T> void RemoveComponent( Entity entity );
	template<typename T> bool HasComponent( Entity entity ) const;

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

	const auto componentId = Component<T>::GetId;

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

		Pool<T>* newComponentPool = new Pool<T>();
		componentPools[componentId] = newComponentPool;
	}

	Pool<T>* componentPool = Pool<T>( componentPools[componentId] );

	if ( entityId >= componentPool->GetSize() ) {
		
		componentPool->Resize( numEntities );
	}

	T newComponent( std::forward<TArgs>( args )... );

	componentPool->Set( entityId, newComponent );

	entityComponentSignature[entityId].set( componentId );
}


template<typename T>
void Registry::RemoveComponent( Entity entity ) {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignature[entityId].set( componentId, false );
}


template<typename T>
bool Registry::HasComponent( Entity entity ) const {

	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignature[entityId].test( componentId );
}


template<typename T, typename ...TArgs>
void Registry::AddSystem( TArgs&& ...args ) {

	T* newSystem( new T( std::forward<TArgs>( args )... ) );
	systems.insert(std::make_pair( std::type_index( typeid( T ) ), newSystem ) );
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

}



#endif // !ECS_H