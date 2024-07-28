#ifndef EVENTBUS_H
#define EVENTBUS_H


#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <memory>


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
