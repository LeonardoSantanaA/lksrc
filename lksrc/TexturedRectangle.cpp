#include "TexturedRectangle.h"
#include <iostream>

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, const ImageFormat& format) : mRect() {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath, format);
	mTexture = SDL_CreateTextureFromSurface(renderer, retrieveSurface); //copy the surface to texture
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}

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

SDL_bool TexturedRectangle::IsColliding(const TexturedRectangle& otherRect) {
	const SDL_Rect temp = otherRect.GetRectangle();
	return SDL_HasIntersection(&mRect, &temp);
}

void TexturedRectangle::Update() {

}

void TexturedRectangle::Draw(int x, int y, int w, int h, float scale) {
	mRect.x = x;
	mRect.y = y;
	mRect.w = static_cast<int>(w * scale);
	mRect.h = static_cast<int>(h * scale);
}


void TexturedRectangle::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, mTexture, NULL, &mRect);
}
