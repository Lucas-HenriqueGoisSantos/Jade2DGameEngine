#include "AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL_image.h>


AssetStore::AssetStore() {

	Logger::Log( "AssetStore constructor called!" );
}

AssetStore::~AssetStore() {

	Logger::Log( "AssetStore destructor called!" );
}


void AssetStore::ClearAssets() {

}

void AssetStore::AddTexture( const std::string& assetId, const std::string& filePath ) {

	SDL_Surface* surface = IMG_Load( filePath.c_str() );
	SDL_Texture* texture = SDL_CreateTextureFromSurface( surface );
}

SDL_Texture* AssetStore::GetTexture( const std::string& assetId ) const {

}