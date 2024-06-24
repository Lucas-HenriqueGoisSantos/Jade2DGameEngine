#include "Game.h"
#include <iostream>

Game::Game() {
	std::cout << "It works!!" << std::endl;
}

Game::~Game() {
	std::cout << "It also works!!" << std::endl;
}


void Game::Inicialize() {

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
	
}