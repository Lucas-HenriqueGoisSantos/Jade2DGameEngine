#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H


#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"


class KeyboardControlSystem : public System {

public:
	KeyboardControlSystem() {}


	void OnKeyPressed( KeyPressedEvent& event ) {

		std::string keyCode = std::to_string( event.symbol );
		std::string keySymbol( 1, event.symbol );

		Logger::Log( "Key pressed event emitted: [" + keyCode + "] " + keySymbol );
	}

	void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus ) {

		eventBus->SubscribeToEvent<KeyPressedEvent>( this, &KeyboardControlSystem::OnKeyPressed );
	}

	void Update() {

	}
};


#endif // !KEYBOARDCONTROLSYSTEM_H