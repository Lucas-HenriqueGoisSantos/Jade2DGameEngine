#include "AssetStore.h"
#include "../Logger/Logger.h"


AssetStore::AssetStore() {

	Logger::Log( "AssetStore constructor called!" );
}

AssetStore::~AssetStore() {

	Logger::Log( "AssetStore destructor called!" );
}


void AssetStore::ClearAssets() {

}

void AssetStore::AddTexture( const std::string& assetId, const std::string& filePath ) {

}

SDL_Texture* AssetStore::GetTexture( const std::string& assetId ) const {

}