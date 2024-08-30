#ifndef LEVELLOADER_H
#define LEVELLOADER_H


#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <sol/sol.hpp>
#include <SDL.h>
#include <memory>


class LevelLoader {

	public:
		LevelLoader();
		~LevelLoader();

		void LoadLevel( sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int levelNumber );
};
#endif // !LEVELLOADER_H
