#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/ProjectileLifeCycleSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RenderHealthBarSystem.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>


int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;

Game::Game() {

	isRunning = false;
	isDebug = false;

	registry = std::make_unique<Registry>();
	assetStore = std::make_unique<AssetStore>();
	eventBus = std::make_unique<EventBus>();

	Logger::Log( "Game constroctor called correctly!" );
}

Game::~Game() {

	Destroy();
	Logger::Log( "Game destructor called correctly!" );
}



void Game::Initialize() {

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {

		Logger::Err( "Error initializing SDL." );
		return;
	}

	if ( TTF_Init() != 0 ) {

		Logger::Err( "Error initializing SDL TTF." );
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

	// Initializing thr ImGui context
	ImGui::CreateContext();
	ImGuiSDL::Initialize( renderer, windowWidth, windowHeight );

	// Change video mode to fullscreen
	SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );

	
	camera.x = 0;
	camera.y = 0;
	camera.w = windowWidth;
	camera.h = windowHeight;


	isRunning = true;
}


void Game::LoadLevel( int level ) {

	// Add the systems here
	registry->AddSystem<MovementSystem>();
	registry->AddSystem<RenderSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<CollisionSystem>();
	registry->AddSystem<RenderColliderSystem>();
	registry->AddSystem<DamageSystem>();
	registry->AddSystem<KeyboardControlSystem>();
	registry->AddSystem<CameraMovementSystem>();
	registry->AddSystem<ProjectileEmitSystem>();
	registry->AddSystem<ProjectileLifeCycleSystem>();
	registry->AddSystem<RenderTextSystem>();
	registry->AddSystem<RenderHealthBarSystem>();


	// Add assets here
	assetStore->AddTexture( renderer, "chopper-image", "./assets/images/chopper-spritesheet.png" );
	assetStore->AddTexture( renderer, "radar-image", "./assets/images/radar.png" );
	assetStore->AddTexture( renderer, "tank-image", "./assets/images/tank-panther-right.png" );
	assetStore->AddTexture( renderer, "truck-image", "./assets/images/truck-ford-right.png" );
	assetStore->AddTexture( renderer, "tilemap-image", "./assets/tilemaps/jungle.png" );
	assetStore->AddTexture( renderer, "bullet-image", "./assets/images/bullet.png" );

	assetStore->AddFont( "charriot-font-20", "./assets/fonts/charriot.ttf", 20 );
	assetStore->AddFont( "pico8-font-5", "./assets/fonts/pico8.ttf", 5 );
	assetStore->AddFont("pico8-font-10", "./assets/fonts/pico8.ttf", 10);


	// Load Tilemap
	int tileSize = 32;
	double tileScale = 2.0;
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
			tile.Group( "tiles" );
			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
		}
	}
	mapFile.close();
	mapWidth = mapNumCols * tileSize * tileScale;
	mapHeight = mapNumRows * tileSize * tileScale;


	// Create and add components to entities here
	Entity chopper = registry->CreateEntity();
	chopper.Tag( "player" );
	chopper.AddComponent<TransformComponent>( glm::vec2( 10.0, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	chopper.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
	chopper.AddComponent<SpriteComponent>( "chopper-image", 32, 32, 2 );
	chopper.AddComponent<AnimationComponent>( 2, 12 );
	chopper.AddComponent<KeyboardControlledComponent>( glm::vec2( 0, -80 ), glm::vec2( 80, 0 ), glm::vec2( 0, 80 ), glm::vec2( -80, 0 ) );
	chopper.AddComponent<CameraFollowComponent>();
	chopper.AddComponent<HealthComponent>( 100 );
	chopper.AddComponent<BoxColliderComponent>( 32, 32 );
	chopper.AddComponent<ProjectileEmitterComponent>(glm::vec2( 150.0, 150.0), 0, 10000, 10, true );


	Entity radar = registry->CreateEntity();
	radar.AddComponent<TransformComponent>( glm::vec2( 500.0, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	radar.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
	radar.AddComponent<SpriteComponent>( "radar-image", 64, 64, 3, true );
	radar.AddComponent<AnimationComponent>( 7, 8 );

	Entity tank = registry->CreateEntity();
	tank.Group( "enemies" );
	tank.AddComponent<TransformComponent>( glm::vec2( 10.0, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	tank.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
	tank.AddComponent<SpriteComponent>( "tank-image", 32, 32, 1 );
	tank.AddComponent<BoxColliderComponent>( 32, 32 );
	tank.AddComponent<ProjectileEmitterComponent>( glm::vec2( 0.0, 50.0 ), 1000, 1000, 10, false );
	tank.AddComponent<HealthComponent>( 100 );

	Entity truck = registry->CreateEntity();
	truck.Group( "enemies" );
	truck.AddComponent<TransformComponent>( glm::vec2( 500.0, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
	truck.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
	truck.AddComponent<SpriteComponent>( "truck-image", 32, 32, 1 );
	truck.AddComponent<BoxColliderComponent>( 32, 32 );
	truck.AddComponent<ProjectileEmitterComponent>( glm::vec2( 50.0, 0.0 ), 1000, 1000, 10, false );
	truck.AddComponent<HealthComponent>( 100 );

	Entity label = registry->CreateEntity();
	SDL_Color white = { 255, 255, 255 };
	label.AddComponent<TextLabelComponent>( glm::vec2( windowWidth/2 - 40 , 100 ), "CHOPPER GAME v 1.0", "charriot-font-20", white, true );
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
			// ImGui SDL Inputs
			ImGui_ImplSDL2_ProcessEvent( &sdlEvent );
			ImGuiIO& io = ImGui::GetIO();

			int mouseX, mouseY;
			const int buttons = SDL_GetMouseState( &mouseX, &mouseY );

			io.MousePos = ImVec2( mouseX, mouseY );
			io.MouseDown[0] = buttons & SDL_BUTTON( SDL_BUTTON_LEFT );
			io.MouseDown[1] = buttons & SDL_BUTTON( SDL_BUTTON_RIGHT );

			// SDL Events
			case SDL_QUIT:
				
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if ( sdlEvent.key.keysym.sym == SDLK_ESCAPE ) {
					
					isRunning = false;
				}

				if ( sdlEvent.key.keysym.sym == SDLK_d ) {

					isDebug = !isDebug;
				}

				eventBus->EmitEvent<KeyPressedEvent>( sdlEvent.key.keysym.sym );

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

	// Reset all event handlers
	eventBus->Reset();

	//-------------------------------------------------------------------------------------------//
	// Performs events subscribtion to all systems ----------------------------------------------------------//
	registry->GetSystem<DamageSystem>().SubscribeToEvents( eventBus );
	registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents( eventBus );
	registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents( eventBus );
	//-------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------//
	// Adds and removes entities from the registry
	registry->Update();
	//-------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------//
	// Update all the systems -------------------------------------------------------------------//
	registry->GetSystem<MovementSystem>().Update( deltaTime );
	registry->GetSystem<AnimationSystem>().Update();
	registry->GetSystem<CollisionSystem>().Update( eventBus );
	registry->GetSystem<ProjectileEmitSystem>().Update( registry );
	registry->GetSystem<CameraMovementSystem>().Update( camera );
	registry->GetSystem<ProjectileLifeCycleSystem>().Update();
	//-------------------------------------------------------------------------------------------//
}

void Game::Render() {

	SDL_SetRenderDrawColor( renderer, 14, 178, 66, 255 );

	SDL_RenderClear( renderer );

	// Render objects here;

	//-------------------------------------------------------------------------------------------//
	// Ivoke all the systems that need to render ------------------------------------------------//
	registry->GetSystem<RenderSystem>().Update( renderer, assetStore, camera );
	registry->GetSystem<RenderTextSystem>().Update( renderer, assetStore, camera );
	registry->GetSystem<RenderHealthBarSystem>().Update( renderer, assetStore, camera );
	if ( isDebug ) {

		registry->GetSystem<RenderColliderSystem>().Update( renderer, camera );
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}


	SDL_RenderPresent( renderer );
}

void Game::Destroy() {

	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}