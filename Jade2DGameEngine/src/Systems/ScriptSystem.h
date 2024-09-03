#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H


#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"
#include "../Components/TransformComponent.h"


void SetEntityPosition( Entity entity, double posX, double posY) {

    if ( entity.HasComponent<TransformComponent>() ) {

        auto transform = entity.GetComponent<TransformComponent>();
        transform.position.x = posX;
        transform.position.y = posY;
    } else {

        Logger::Err( "Trying to set the position of a entity without a transform component" );
    }
}


class ScriptSystem: public System {

    public:
        ScriptSystem() {

            RequireComponent<ScriptComponent>();
        }

        void CreateLuaBindings( sol::state& lua ) {

            lua.new_usertype<Entity>(
                "entity",
                "get_id", &Entity::GetId,
                "destroy", &Entity::Kill,
                "has_tag", &Entity::HasTag,
                "belongs_to_group", &Entity::BelongsToGroup
            );

            lua.set_function( "set_position", SetEntityPosition );
        }

        void Update( double deltaTime, int ellapsedTime ) {

            for ( auto entity: GetSystemEntities() ) {

                const auto script = entity.GetComponent<ScriptComponent>();
                script.func( entity, deltaTime, ellapsedTime );
            }
        }
};

#endif