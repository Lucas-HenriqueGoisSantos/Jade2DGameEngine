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

    sol::load_result script = lua.load_file( "./assets/scripts/Level" + std::to_string( levelNumber ) + ".lua" );

    // Checks the syntex of the script without executing it
    if ( !script.valid() ) {

        sol::error err = script;
        std::string errorMessage = err.what();

        Logger::Err( "Error loading the Lua script: " + errorMessage );

        return;
    }

    lua.script_file( "./assets/scripts/Level" + std::to_string( levelNumber ) + ".lua" );

    sol::table level = lua["Level"];

    ///////////////////////////////////////////////////////////////////////////
    // Read the level assets
    ///////////////////////////////////////////////////////////////////////////
    sol::table assets = level["assets"];

    int i = 0;
    while ( true ) {

        sol::optional<sol::table> hasAsset = assets[i];
        if (hasAsset == sol::nullopt ) {

            break;
        }

        sol::table asset = assets[i];
        std::string assetType = asset["type"];
        std::string assetId = asset["id"];

        if ( assetType == "texture" ) {

            assetStore->AddTexture( renderer, assetId, asset["file"] );
        }

        if ( assetType == "font" ) {

            assetStore->AddFont( assetId, asset["file"], asset["font_size"] );
        }


        i++;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Read the level tilemap information
    ///////////////////////////////////////////////////////////////////////////
    sol::table map = level["tilemap"];
    std::string mapFilePath = map["map_file"];
    std::string mapTextureId = map["texture_asset_id"];
    int mapNumRows = map["num_rows"];
    int mapNumCols = map["num_cols"];
    int tileSize = map["tile_size"];
    double mapScale = map["scale"];

    std::fstream mapFile;
    mapFile.open( mapFilePath );
    for ( int y = 0; y < mapNumRows; y++ ) {

        for ( int x = 0; x < mapNumCols; x++ ) {

            char ch;

            mapFile.get( ch );
            int srcRectY = std::atoi( &ch ) * tileSize;

            mapFile.get( ch );
            int srcRectX = std::atoi( &ch ) * tileSize;

            mapFile.ignore();

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>( glm::vec2( x * ( mapScale * tileSize ), y * ( mapScale * tileSize ) ), glm::vec2( mapScale, mapScale ), 0.0 );
            tile.AddComponent<SpriteComponent>( mapTextureId, tileSize, tileSize, 0, false, srcRectX, srcRectY );
        }
    }
    mapFile.close();
    Game::mapWidth = mapNumCols * tileSize * mapScale;
    Game::mapHeight = mapNumRows * tileSize * mapScale;

    ///////////////////////////////////////////////////////////////////////////
    // Read the level entities and their components
    ///////////////////////////////////////////////////////////////////////////
    sol::table entities = level["entities"];

    i = 0;
    while ( true ) {

        sol::optional<sol::table> hasEntity = entities[i];
        if ( hasEntity == sol::nullopt ) {

            break;
        }

        sol::table entity = entities[i];

        Entity newEntity = registry->CreateEntity();

        // Tag
        sol::optional<std::string> tag = entity["tag"];
        if ( tag != sol::nullopt ) {

            newEntity.Tag( entity["tag"] );
        }
        // Group
        sol::optional<std::string> group = entity["group"];
        if ( group != sol::nullopt ) {

            newEntity.Group( entity["group"] );
        }

        // Components
        sol::optional<sol::table> hasComponent = entity["components"];
        if ( hasComponent != sol::nullopt ) {

            // Transform
            sol::optional<sol::table> transform = entity["components"]["transform"];
            if ( transform != sol::nullopt ) {

                newEntity.AddComponent<TransformComponent>(
                    glm::vec2(
                        static_cast<float>( entity["components"]["transform"]["position"]["x"] ) * Game::globalRenderScale,
                        static_cast<float>( entity["components"]["transform"]["position"]["y"] ) * Game::globalRenderScale
                    ),
                    glm::vec2(
                        static_cast<float>( entity["components"]["transform"]["scale"]["x"].get_or( 1.0 ) ) * Game::globalRenderScale,
                        static_cast<float>( entity["components"]["transform"]["scale"]["y"].get_or( 1.0 ) ) * Game::globalRenderScale
                    ),
                    entity["components"]["transform"]["rotation"].get_or( 0.0 )
                );
            }

            // Rigidbody
            sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
            if ( rigidbody != sol::nullopt ) {

                newEntity.AddComponent<RigidBodyComponent>(
                    glm::vec2(
                        entity["components"]["rigidbody"]["velocity"]["x"].get_or( 0.0 ),
                        entity["components"]["rigidbody"]["velocity"]["y"].get_or( 0.0 )
                    )
                );
            }

            // Sprite
            sol::optional<sol::table> sprite = entity["components"]["sprite"];
            if ( sprite != sol::nullopt ) {

                newEntity.AddComponent<SpriteComponent>(
                    entity["components"]["sprite"]["texture_asset_id"],
                    entity["components"]["sprite"]["width"],
                    entity["components"]["sprite"]["height"],
                    entity["components"]["sprite"]["z_index"].get_or( 1 ),
                    entity["components"]["sprite"]["fixes"].get_or( false ),
                    entity["components"]["sprite"]["src_rect_x"].get_or( 0 ),
                    entity["components"]["sprite"]["src_rect_y"].get_or( 0 )
                );
            }

            // Animation
            sol::optional<sol::table> animation = entity["components"]["animation"];
            if ( animation != sol::nullopt ) {

                newEntity.AddComponent<AnimationComponent>(
                    entity["components"]["animation"]["num_frames"].get_or( 1 ),
                    entity["components"]["animation"]["speed_rate"].get_or( 1 ),
                    entity["components"]["animation"]["loop"].get_or( false )
                );
            }

            // BoxCollider
            sol::optional<sol::table> collider = entity["components"]["boxcollider"];
            if (collider != sol::nullopt ) {

                newEntity.AddComponent<BoxColliderComponent>(
                    entity["components"]["boxcollider"]["width"],
                    entity["components"]["boxcollider"]["height"],
                    glm::vec2(
                        entity["components"]["boxcollider"]["offset"]["x"].get_or( 0 ),
                        entity["components"]["boxcollider"]["offset"]["y"].get_or( 0 )
                    )
                );
            }

            // Health
            sol::optional<sol::table> health = entity["components"]["health"];
            if ( health != sol::nullopt ) {

                newEntity.AddComponent<HealthComponent>(
                    static_cast<int>( entity["components"]["health"]["health_percentage"].get_or( 100 ) )
                );
            }

            // Projectile Emitter
            sol::optional<sol::table> emitter = entity["components"]["projectile_emitter"];
            if ( emitter != sol::nullopt ) {

                newEntity.AddComponent<ProjectileEmitterComponent>(
                    glm::vec2(
                        entity["components"]["projectile_emitter"]["projectile_velocity"]["x"],
                        entity["components"]["projectile_emitter"]["projectile_velocity"]["y"]
                    ),
                    static_cast<int>( entity["components"]["projectile_emitter"]["repeat_frequency"].get_or( 1 ) ) * 1000,
                    static_cast<int>( entity["components"]["projectile_emitter"]["projectile_duration"].get_or( 10000 ) ) * 1000,
                    static_cast<int>( entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or( 10 ) ),
                    static_cast<int>( entity["components"]["projectile_emitter"]["friendly"].get_or( false ) )
                );
            }

            // Keyboard Controller
            sol::optional<sol::table> keyboard = entity["components"]["keyboard_controller"];
            if ( keyboard != sol::nullopt ) {

                newEntity.AddComponent<KeyboardControlledComponent>(
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["up_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["up_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["right_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["right_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["down_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["down_velocity"]["y"]
                    ),
                    glm::vec2(
                        entity["components"]["keyboard_controller"]["left_velocity"]["x"],
                        entity["components"]["keyboard_controller"]["left_velocity"]["y"]
                    )
                );
            }

            // Camera Follow
            sol::optional<sol::table> follow = entity["components"]["camera_follow"];
            if ( follow != sol::nullopt ) {
                newEntity.AddComponent<CameraFollowComponent>();
            }
        }

        i++;
    }

    // // Adding assets to the Level
    // assetStore->AddTexture( renderer, "radar-image", "./assets/images/radar.png" );


    // // Create, tag and adds components to entities -------------------------------------- //
    // // ---------------------------------------------------------------------------------- //

    // // UI Radar
    // Entity radar = registry->CreateEntity();
    // radar.AddComponent<TransformComponent>( glm::vec2( Game::windowWidth - 74, 10.0 ), glm::vec2( 1.0, 1.0 ), 0.0 );
    // radar.AddComponent<RigidBodyComponent>( glm::vec2( 0.0, 0.0 ) );
    // radar.AddComponent<SpriteComponent>( "radar-image", 64, 64, 1, true );
    // radar.AddComponent<AnimationComponent>( 8, 5, true );

    // // Enemy Tank
    // tank.AddComponent<RigidBodyComponent>( glm::vec2( 20.0, 0.0 ) );

    // // UI Label
    // Entity label = registry->CreateEntity();
    // SDL_Color green = { 0, 255, 0 };
    // label.AddComponent<TextLabelComponent>( glm::vec2( Game::windowWidth / 2 - 40, 10 ), "CHOPPER 1.0", "pico8-font-10", green, true );
}