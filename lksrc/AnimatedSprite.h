#pragma once

#include <string>

#include <SDL.h>
#include "ResourceManager.h"
#include "GlobalResources.h"

class AnimatedSprite {
public:
	AnimatedSprite(SDL_Renderer* render, const std::string& filepath, const ImageFormat& format = FORMAT_BMP);
	~AnimatedSprite();

	void PlayFrame(int x, int y, int w, int h, int frame);

	void Update();
	void Render(SDL_Renderer*& render);

	void SetPosition(int x, int y);
	void SetDimensions(int w, int h, float scale);

	inline void SetCountSpeed(float speed) { mCountSpeed = speed; }

private:
	int mCountSpeed;
	SDL_Rect mSrc;	//where we're selecting from
	SDL_Rect mDst;	//where we're rendering
	SDL_Texture* mTexture;
};