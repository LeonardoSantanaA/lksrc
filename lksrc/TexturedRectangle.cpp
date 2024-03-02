#include "TexturedRectangle.h"
#include <iostream>

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, const ImageFormat& format, float scale) {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath, format);
	mTexture = SDL_CreateTextureFromSurface(renderer, retrieveSurface); //copy the surface to texture
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}

	mRect.x = 0;
	mRect.y = 0;
	mRect.w = static_cast<int>(32 * scale);
	mRect.h = static_cast<int>(32 * scale);

}

TexturedRectangle::TexturedRectangle(const TexturedRectangle& other)
	:mRect(other.mRect), mTexture(other.mTexture) {
}

TexturedRectangle& TexturedRectangle::operator=(const TexturedRectangle& other) {
	if (this != &other) {
		mRect = other.mRect;
		mTexture = other.mTexture;
	}
	return *this;
}

TexturedRectangle::~TexturedRectangle() {
	SDL_DestroyTexture(mTexture);
}

void TexturedRectangle::Update() {

}

void TexturedRectangle::SetPosition(int x, int y) {
	mRect.x = x;
	mRect.y = y;
}

void TexturedRectangle::SetDimensions(int w, int h, float scale) {
	mRect.w = static_cast<int>(w * scale);
	mRect.h = static_cast<int>(h * scale);
}


void TexturedRectangle::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, mTexture, NULL, &mRect);
}
