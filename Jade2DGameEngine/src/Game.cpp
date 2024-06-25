#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
	std::cout << "It works!!" << std::endl;
}

Game::~Game() {
	std::cout << "It also works!!" << std::endl;
}


void Game::Inicialize() {

	if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		std::cerr << "Error inicializing SDL." << std::endl;
		return;
	}

	window = SDL_CreateWindow( NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS );
	if ( !window ) {
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer( window, -1, 0 );
	if ( !renderer ) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}
}

void Game::Run() {

	while ( true ) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {

}

void Game::Update() {

}

void Game::Render() {

}

void Game::Destroy() {
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}