#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "../ECS/ECS.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {

private:
	bool isRunning;
	int millisecondsPreviousFrame = 0;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	Registry* registry;

public:
	Game();
	~Game();

	void Setup();
	void Run();
	void Inicialize();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidth = 800;
	int windowHeight = 600;

};

#endif
