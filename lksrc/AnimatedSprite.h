#pragma once

#include <string>

#include <SDL.h>
#include "ResourceManager.h"
#include "GlobalResources.h"

class AnimatedSprite {
public:
	AnimatedSprite(SDL_Renderer* render, const std::string& filepath, const ImageFormat& format = FORMAT_BMP);
	~AnimatedSprite();

	void Draw(int x, int y, int w, int h, float scale = SCALE);

	void PlayFrame(int x, int y, int w, int h, int frame);

	void Update();

	void Render(SDL_Renderer*& render);

private:
	SDL_Rect mSrc;	//where we're selecting from
	SDL_Rect mDst;	//where we are rendering
	SDL_Texture* mTexture;
};