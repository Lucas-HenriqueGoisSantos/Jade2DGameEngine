#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {

private:
	bool isRunning;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

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
