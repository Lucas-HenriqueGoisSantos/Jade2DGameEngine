#include "AssetStore.h"
#include "../Logger/Logger.h"


AssetStore::AssetStore() {

	Logger::Log( "AssetStore constructor called!" );
}

AssetStore::~AssetStore() {

	Logger::Log("AssetStore destructor called!");
}


void ClearAssets() {

}

void AddTexture(const std::string& assetId, const std::string& filePath) {

}

SDL_Texture* GetTexture(const std::string& assetId) const {

}