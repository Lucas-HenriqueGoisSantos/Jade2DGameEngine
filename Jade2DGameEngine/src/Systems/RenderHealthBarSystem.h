#ifndef RENDERHEALTHBARSYSTEM_H
#define RENDERHEALTHBARSYSTEM_H


#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL.h>


class RenderHealthBarSystem: public System {

public:
	RenderHealthBarSystem() {

	}

	void Update( SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera ) {

	}
};


#endif // !RENDERHEALTHBARSYSTEM_H