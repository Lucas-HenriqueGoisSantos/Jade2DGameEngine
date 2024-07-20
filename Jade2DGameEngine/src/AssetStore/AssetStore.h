#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL.h>


class AssetStore {

private:
	std::map<std::string, SDL_Texture*> textures;

public:
	AssetStore();
	~AssetStore();

	void ClearAssets();
	void AddTexture( const std::string& assetId, const string& filePath );
	SDL_Texture* GetTexture( const std::string& assetId ) const;
};


#endif // !ASSETSTORE_H

