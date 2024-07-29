#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <memory>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {

private:
	bool isRunning;
	bool isDebug;
	int millisecondsPreviousFrame = 0;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	std::unique_ptr<Registry> registry;
	std::unique_ptr<AssetStore> assetStore;
	std::unique_ptr<EventBus> eventBus;

public:
	Game();
	~Game();

	void Inicialize();
	void LoadLevel( int level );
	void Setup();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidth = 800;
	int windowHeight = 600;

};

#endif
