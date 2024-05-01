#pragma once

#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
public:
	static TextureManager* GetInstance();

	bool Load(const std::string& id, const std::string& path);
	void Drop(std::string id);
	void Clean();

	void Render(const std::string& id, int x, int y, int w, int h, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void RenderFrame(const std::string& id, int x, int y, int w, int h, int row, int frame, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void RenderTile(const std::string& tilesetID, int tileSize, int x, int y, int row, int frame, const SDL_RendererFlip& flip = SDL_FLIP_NONE);

private:
	static TextureManager* mInstance;
	std::map<std::string, SDL_Texture*> mTextureMap;


};