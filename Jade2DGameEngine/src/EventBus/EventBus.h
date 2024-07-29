#ifndef EVENTBUS_H
#define EVENTBUS_H


#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <memory>
#include <list>


class Event {

public:
	Event() = default;
};

class IEventCallback {

private:
	virtual void Call( Event& e ) = 0;

public:
	virtual ~IEventCallback() = default;

	void Execute( Event& e ) {

		Call( e );
	}
};

template<typename TOwner, typename T> class EventCallback: public IEventCallback {

private:
	typedef void ( TOwner::* CallBackFunction ) ( T& );

	TOwner ownerInstance;
	CallbackFunction callbackFunction;

	virtual void Call( Event& e ) override {

	std:invoke( callbackFunction, ownerInstance, static_cast<TEvent&>( e ) );
	}

public:
	EventCallback( TOwner ownerInstance, CallBackFunction callbackFunction ) {

		this->ownerInstance = ownerInstance;
		this->callbackFunction = callbackFunction;
	}

	virtual ~EventCallback() override = default;
};


typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;


class EventBus {

private:
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:
	EventBus() {

		Logger::Log( "EventBus constructor called!" );
	}

	~EventBus() {

		Logger::Log( "EventBus destructor called!" );
	}

	template<typename TOwner, typename T>
	void SubscribeToEvent( TOwner* ownerInstance, void( TOwner::*callbackFunction )( T& ) ) {

		if ( !subscribers[typeid( T )].get() ) {

			subscribers[typeid( T )] == std::make_unique<HandlerList>();
		}

		auto subscriber = std::make_unique<EventCallback<TOwner, T>>( ownerInstance, callbackFunction );
		subscribers[typeid( T )]->push_back( std::move( subscriber ) );
	}

	template<typename T, typename ...TArgs>
	void EmitEvent( TArgs&& ...args ) {

		auto handlers = subscribers[typeid( T )].get();

		if ( handlers ) {

			for ( auto it = handlers->begin(); it != handlers->end(); it++ ) {
				
				auto handler = it->get();
				T event( std::forward<TArgs>( args )... );

				handler->Execute( event );
			}
		}
	}
};



#endif // !EVENTBUS_H
