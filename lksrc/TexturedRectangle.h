#pragma once

#include <iostream>
#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GlobalResources.h"

class TexturedRectangle {
public:
	TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	TexturedRectangle(const TexturedRectangle& other);
	TexturedRectangle& operator=(const TexturedRectangle& other);
	~TexturedRectangle();

	SDL_bool IsColliding(const TexturedRectangle& otherRect);

	void Update();
	void SetPosition(int x, int y);
	void SetDimensions(int w, int h, float scale = SCALE);
	void Render(SDL_Renderer* renderer);

private:
	inline SDL_Rect GetRectangle() const { return mRect; }

	SDL_Rect mRect;
	SDL_Texture* mTexture;
};