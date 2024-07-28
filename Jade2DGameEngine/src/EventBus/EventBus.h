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

		std:invoke( callbackFunction, ownerInstance, e );
	}
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


	void SubscribeToEvent<___>() {


	}

	void EmitEvent<___>() {


	}
};



#endif // !EVENTBUS_H
