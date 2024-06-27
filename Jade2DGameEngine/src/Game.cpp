#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
	isRunning = false;
	std::cout << "It works!!" << std::endl;
}

Game::~Game() {
	std::cout << "It also works!!" << std::endl;
}



void Game::Setup() {
	// Inicialize game objects
}


void Game::Run() {

	Setup();

	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}


void Game::Inicialize() {

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
		std::cerr << "Error inicializing SDL." << std::endl;
		return;
	}

	// Sets the game to "fake" fullscreen
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode( 0, &displayMode );

	windowWidth = 800; // displayMode.w;
	windowHeight = 600; // displayMode.h;


	window = SDL_CreateWindow( 
		NULL, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_BORDERLESS 
	);
	if ( !window ) {
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer( 
		window, 
		-1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if ( !renderer ) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	// Change video mode to fullscreen
	SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );
	
	isRunning = true;
}


void Game::ProcessInput() {

	SDL_Event sdlEvent;
	while ( SDL_PollEvent( &sdlEvent ) ) {

		switch ( sdlEvent.type ) {

			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if ( sdlEvent.key.keysym.sym == SDLK_ESCAPE ) {
					isRunning = false;
				}
				break;

			default:
				break;
		}
	}
}

void Game::Update() {

}

void Game::Render() {
	SDL_SetRenderDrawColor( renderer, 14, 178, 66, 255);

	SDL_RenderClear( renderer );

	// Render objects here;

	// Render of a white rectangle
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect playerExemple = { 10, 10, 20, 30 };
	SDL_RenderFillRect( renderer, &playerExemple );


	SDL_RenderPresent( renderer );
}

void Game::Destroy() {
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}