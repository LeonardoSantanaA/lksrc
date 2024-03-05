#pragma once

#include <iostream>
#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GlobalResources.h"

class TexturedRectangle {
public:
	TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, int redColorKey, int greenColorKey, int blueColorKey, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	void Init();
	TexturedRectangle(const TexturedRectangle& other);
	TexturedRectangle& operator=(const TexturedRectangle& other);
	~TexturedRectangle();

	void Update();
	void SetPosition(int x, int y);
	void SetDimensions(int w, int h, float scale = SCALE);
	void Render(SDL_Renderer* renderer);

	inline int GetX() const { return mRect.x; }
	inline int GetY() const { return mRect.y; }
	inline int GetWidth() const { return mRect.w; }
	inline int GetHeight() const { return mRect.h; }

	void SetColorKey(int red, int green, int blue);

private:
	inline SDL_Rect GetRectangle() const { return mRect; }

	SDL_Rect mRect;
	SDL_Texture* mTexture;

	int mRedColorKey;
	int mGreenColorKey;
	int mBlueColorKey;
};