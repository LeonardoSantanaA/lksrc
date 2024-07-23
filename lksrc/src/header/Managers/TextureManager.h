#pragma once

#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
public:
	static TextureManager* GetInstance();

	//Load only .png images!
	bool Load(const std::string& id, const std::string& path);

	//clean specific texture
	void Drop(std::string id);

	void Clean();

	//render a background or another image with scroll ratio, its perfect to draw backgrounds
	void Render(const std::string& id, int x, int y, int w, int h, float xScale = 1, float yScale = 1, float scrollRatio = 0, bool loop = false, const SDL_RendererFlip& flip = SDL_FLIP_NONE);

	void RenderFrame(const std::string& id, int x, int y, int w, int h, int row, int frame, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void RenderTile(const std::string& tilesetID, int tileSize, int x, int y, int row, int frame, const SDL_RendererFlip& flip = SDL_FLIP_NONE);

private:
	TextureManager() {};
	static TextureManager* mInstance;
	std::map<std::string, SDL_Texture*> mTextureMap;


};