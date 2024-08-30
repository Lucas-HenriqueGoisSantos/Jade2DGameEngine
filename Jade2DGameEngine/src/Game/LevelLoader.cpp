#include "./LevelLoader.h"
#include "./Game.h"
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
#include <sol/sol.hpp>
#include <fstream>


LevelLoader::LevelLoader() {

    Logger::Log( "LevelLoader constructor called" );
}
LevelLoader::~LevelLoader() {

    Logger::Log( "LevelLoader destructor called" );
}

void LevelLoader::LoadLevel( sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer,  int levelNumber ) {

    lua.script_file( "./assets/scripts/Level" + std::to_string( levelNumber ) + ".lua" );
    // TODO: Load level from lua instead

    // // Adding assets to the Level
    // assetStore->AddTexture( renderer, "tank-image", "./assets/images/tank-panther-right.png" );
    // assetStore->AddTexture( renderer, "truck-image", "./assets/images/truck-ford-right.png" );
    // assetStore->AddTexture( renderer, "chopper-image", "./assets/images/chopper-spritesheet.png" );
    // assetStore->AddTexture( renderer, "radar-image", "./assets/images/radar.png" );
    // assetStore->AddTexture( renderer, "tilemap-image", "./assets/tilemaps/jungle.png" );
    // assetStore->AddTexture( renderer, "bullet-image", "./assets/images/bullet.png" );
    // assetStore->AddTexture( renderer, "tree-image", "./assets/images/tree.png" );
    // assetStore->AddFont( "charriot-font-20", "./assets/fonts/charriot.ttf", 20 );
    // assetStore->AddFont( "pico8-font-5", "./assets/fonts/pico8.ttf", 5 );
    // assetStore->AddFont( "pico8-font-10", "./assets/fonts/pico8.ttf", 10 );

    // // Load the Level tilemap
    // int tileSize = 32;
    // double tileScale = 3.0;
    // int mapNumCols = 25;
    // int mapNumRows = 20;

    // std::fstream mapFile;
    // mapFile.open( "./assets/tilemaps/jungle.map" );

    // for ( int y = 0; y < mapNumRows; y++ ) {

    //     for ( int x = 0; x < mapNumCols; x++ ) {

    //         char ch;
    //         mapFile.get( ch );
    //         int srcRectY = std::atoi( &ch ) * tileSize;
    //         mapFile.get( ch );
    //         int srcRectX = std::atoi( &ch ) * tileSize;
    //         mapFile.ignore();

    //         Entity tile = registry->CreateEntity();
    //         tile.Group( "tiles" );
    //         tile.AddComponent<TransformComponent>( glm::vec2( x * ( tileScale * tileSize ), y * ( tileScale * tileSize ) ), glm::vec2( tileScale, tileScale ), 0.0 );
    //         tile.AddComponent<SpriteComponent>( "tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY );
    //     }
    // }
    // mapFile.close();
    // Game::mapWidth = mapNumCols * tileSize * tileScale;
    // Game::mapHeight = mapNumRows * tileSize * tileScale;


    // // Create, tag and adds components to entities -------------------------------------- //
    // // ---------------------------------------------------------------------------------- //
    // // Player Chopper
    // Entity chopper = registry->CreateEntity();
    // chopper.Tag( "player" );
    // chopper.AddComponent<TransformComponent>( glm::vec2( 360.0, 165.0 ), glm::vec2( 1.5, 1.5 ), 0.0 );
    // chopper.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // chopper.AddComponent<SpriteComponent>( "chopper-image", 32, 32, 1 );
    // chopper.AddComponent<AnimationComponent>( 2, 15, true );
    // chopper.AddComponent<BoxColliderComponent>( 32, 25, glm::vec2( 0, 5 ) );
    // chopper.AddComponent<ProjectileEmitterComponent>( glm::vec2( 150.0, 150.0 ), 0, 10000, 10, true );
    // chopper.AddComponent<KeyboardControlledComponent>( glm::vec2( 0, -50 ), glm::vec2( 50, 0 ), glm::vec2( 0, 50 ), glm::vec2( -50, 0 ) );
    // chopper.AddComponent<CameraFollowComponent>();
    // chopper.AddComponent<HealthComponent>( 100 );

    // // UI Radar
    // Entity radar = registry->CreateEntity();
    // radar.AddComponent<TransformComponent>( glm::vec2( Game::windowWidth - 74, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
    // radar.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // radar.AddComponent<SpriteComponent>( "radar-image", 64, 64, 1, true );
    // radar.AddComponent<AnimationComponent>( 8, 5, true );

    // // Enemy Tank
    // Entity tank = registry->CreateEntity();
    // tank.Group( "enemies" );
    // tank.AddComponent<TransformComponent>( glm::vec2( 750.0, 750.0 ), glm::vec2( 1.5, 1.5 ), 0.0 );
    // tank.AddComponent<RigidBodyComponent>( glm::vec2( 20.0, 0.0 ) );
    // tank.AddComponent<SpriteComponent>( "tank-image", 32, 32, 1 );
    // tank.AddComponent<BoxColliderComponent>( 25, 18, glm::vec2( 5, 7 ) );
    // tank.AddComponent<ProjectileEmitterComponent>( glm::vec2( 100.0, 0.0 ), 3000, 5000, 10, false );
    // tank.AddComponent<HealthComponent>( 100 );

    // // Enemy Truck
    // Entity truck = registry->CreateEntity();
    // truck.Group( "enemies" );
    // truck.AddComponent<TransformComponent>( glm::vec2( 180.0, 750.0 ), glm::vec2( 1.5, 1.5 ), 0.0 );
    // truck.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // truck.AddComponent<SpriteComponent>( "truck-image", 32, 32, 2 );
    // truck.AddComponent<BoxColliderComponent>( 25, 20, glm::vec2( 5, 5 ) );
    // truck.AddComponent<ProjectileEmitterComponent>( glm::vec2( 0.0, -100.0 ), 2000, 5000, 10, false );
    // truck.AddComponent<HealthComponent>( 100 );

    // // Obstacle Tree
    // Entity treeA = registry->CreateEntity();
    // treeA.Group( "obstacles" );
    // treeA.AddComponent<TransformComponent>( glm::vec2( 900.0, 742.5 ), glm::vec2( 1.5, 1.5 ), 0.0 );
    // treeA.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // treeA.AddComponent<SpriteComponent>( "tree-image", 16, 32, 2 );
    // treeA.AddComponent<BoxColliderComponent>( 16, 32 );

    // // Obstacle Tree
    // Entity treeB = registry->CreateEntity();
    // treeB.Group( "obstacles" );
    // treeB.AddComponent<TransformComponent>( glm::vec2( 600.0, 742.5 ), glm::vec2( 1.5, 1.5 ), 0.0 );
    // treeB.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // treeB.AddComponent<SpriteComponent>( "tree-image", 16, 32, 2 );
    // treeB.AddComponent<BoxColliderComponent>( 16, 32 );

    // // UI Label
    // Entity label = registry->CreateEntity();
    // SDL_Color green = { 0, 255, 0 };
    // label.AddComponent<TextLabelComponent>( glm::vec2( Game::windowWidth / 2 - 40, 10 ), "CHOPPER 1.0", "pico8-font-10", green, true );
}