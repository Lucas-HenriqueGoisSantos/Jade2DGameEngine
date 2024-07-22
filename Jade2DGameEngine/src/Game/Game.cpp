#include "Game.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>



Game::Game() {

	isRunning = false;

	registry = std::make_unique<Registry>();
	assetStore = std::make_unique<AssetStore>();

	Logger::Log( "Game constroctor called correctly!" );
}

Game::~Game() {

	Destroy();
	Logger::Log( "Game destructor called correctly!" );
}



void Game::Inicialize() {

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
		Logger::Err( "Error inicializing SDL." );
		return;
	}

	// Sets the game to "fake" fullscreen
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode( 0, &displayMode );

	//windowWidth = 800; // displayMode.w;
	//windowHeight = 600; // displayMode.h;


	window = SDL_CreateWindow(

		NULL,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight,
		SDL_WINDOW_BORDERLESS
	);

	if ( !window ) {

		Logger::Err( "Error creating SDL window." );
		return;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if ( !renderer ) {
		Logger::Err( "Error creating SDL renderer." );
		return;
	}

	// Change video mode to fullscreen
	SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );

	isRunning = true;
}


void Game::LoadLevel( int level ) {

	// Add the systems here
	registry->AddSystem<MovementSystem>();

	registry->AddSystem<RenderSystem>();


	// Add assets here
	assetStore->AddTexture( renderer, "tank-image", "./assets/images/tank-panther-right.png" );
	assetStore->AddTexture( renderer, "truck-image", "./assets/images/truck-ford-right.png" );
	assetStore->AddTexture( renderer, "tilemap-image", "./assets/tilemaps/jungle.png" );


	// Load Tilemap
	int tileSize = 32;
	double tileScale = 1.0;
	int mapNumCols = 25;
	int mapNumRows = 20;
	std::fstream mapFile;
	mapFile.open( "./assets/tilemaps/jungle.map" );
	for (int y = 0; y < mapNumRows; y++) {
		for (int x = 0; x < mapNumCols; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();

			Entity tile = registry->CreateEntity();
			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, srcRectX, srcRectY);
		}
	}
	mapFile.close();


	// Create and add components to entities here
	Entity tank = registry->CreateEntity();
	tank.AddComponent<TransformComponent>( glm::vec2( 10.0, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	tank.AddComponent<RigidBodyComponent>( glm::vec2( 40.0, 0.0 ) );
	tank.AddComponent<SpriteComponent>( "tank-image", 1, 32, 32 );

	Entity truck = registry->CreateEntity();
	truck.AddComponent<TransformComponent>( glm::vec2( 50.0, 100.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	truck.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 50.0 ) );
	truck.AddComponent<SpriteComponent>( "truck-image", 1, 32, 32 );
}


void Game::Setup() {

	LoadLevel( 1 );
}


void Game::Run() {

	Setup();

	while ( isRunning ) {
		ProcessInput();
		Update();
		Render();
	}
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

	//-------------------------------------------------------------------------------------------//
	// Capps the FPS to 60 ----------------------------------------------------------------------//
	//int timeToWait = MILLISECONDS_PER_FRAME - ( SDL_GetTicks() - millisecondsPreviousFrame );
	//if ( timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME ) {
	//	SDL_Delay( timeToWait );
	//}
	//-------------------------------------------------------------------------------------------//

	// Sets deltaTime
	double deltaTime = ( SDL_GetTicks() - millisecondsPreviousFrame ) / 1000.0;
	// Store the current frame time
	millisecondsPreviousFrame = SDL_GetTicks();

	//-------------------------------------------------------------------------------------------//
	// Update all the systems -------------------------------------------------------------------//
	registry->GetSystem<MovementSystem>().Update( deltaTime );
	
	//-------------------------------------------------------------------------------------------//

	// TODO:
	// CollisionSystem.Update();
	// DamegeSystem.Update();

	//-------------------------------------------------------------------------------------------//
	// Adds and removes entities from the registry
	registry->Update();
	//-------------------------------------------------------------------------------------------//
}

void Game::Render() {

	SDL_SetRenderDrawColor( renderer, 14, 178, 66, 255 );

	SDL_RenderClear( renderer );

	// Render objects here;

	//-------------------------------------------------------------------------------------------//
	// Ivoke all the systems that need to render ------------------------------------------------//
	registry->GetSystem<RenderSystem>().Update( renderer, assetStore );
	
	//-------------------------------------------------------------------------------------------//
	// Render of a white rectangle
	//SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	//SDL_Rect playerExemple = { 10, 10, 20, 30 };
	//SDL_RenderFillRect( renderer, &playerExemple );

	//--------------------------------------------------------------------------------//
	//// Render PNG texture

	//// Load PNG from file
	//SDL_Surface* surface = IMG_Load( "./assets/images/tank-tiger-right.png" );
	//SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
	//SDL_FreeSurface( surface );

	//// Destination and size in render
	//SDL_Rect dstRect = { 
	//	static_cast<int>(playerPos.x), static_cast<int>(playerPos.y),
	//	64, 64 
	//};
	//// Copying to the renderer. A NULL SDL_Rect will be interpreted as "get the entire texture / fill the entire window"
	//SDL_RenderCopy( renderer, texture, NULL, &dstRect );
	//SDL_DestroyTexture( texture );
	//--------------------------------------------------------------------------------//


	SDL_RenderPresent( renderer );
}

void Game::Destroy() {

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}