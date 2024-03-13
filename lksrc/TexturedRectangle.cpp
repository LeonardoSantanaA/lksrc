#include "TexturedRectangle.h"
#include <iostream>

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, const ImageFormat& format, float scale)
: mRedColorKey(), mGreenColorKey(), mBlueColorKey(){
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath, format);
	SDL_SetColorKey(retrieveSurface, SDL_FALSE, SDL_MapRGB(retrieveSurface->format, 0xFF, 0xFF, 0xFF));

	mTexture = SDL_CreateTextureFromSurface(renderer, retrieveSurface); //copy the surface to texture
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}

	mRect.x = 0;
	mRect.y = 0;
	mRect.w = static_cast<int>(32 * scale);
	mRect.h = static_cast<int>(32 * scale);
}

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, const std::string& filepath, int redColorKey, int greenColorKey, int blueColorKey, const ImageFormat& format, float scale) {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath, format);
	SDL_SetColorKey(retrieveSurface, SDL_TRUE, SDL_MapRGB(retrieveSurface->format, redColorKey, greenColorKey, blueColorKey));

	mTexture = SDL_CreateTextureFromSurface(renderer, retrieveSurface); //copy the surface to texture
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}

	mRect.x = 0;
	mRect.y = 0;
	mRect.w = static_cast<int>(32 * scale);
	mRect.h = static_cast<int>(32 * scale);

	Init();

	mRedColorKey = redColorKey;
	mGreenColorKey = greenColorKey;
	mBlueColorKey = blueColorKey;
}

void TexturedRectangle::Init() {
	mRedColorKey = 0xFF;
	mGreenColorKey = 0xFF;
	mBlueColorKey = 0xFF;
}

TexturedRectangle::TexturedRectangle(const TexturedRectangle& other)
	:mRect(other.mRect), mTexture(other.mTexture), mRedColorKey(other.mRedColorKey), mGreenColorKey(other.mGreenColorKey), mBlueColorKey(other.mBlueColorKey) {
}

TexturedRectangle& TexturedRectangle::operator=(const TexturedRectangle& other) {
	if (this != &other) {
		mRect = other.mRect;
		mTexture = other.mTexture;
		mRedColorKey = other.mRedColorKey;
		mGreenColorKey = other.mGreenColorKey;
		mBlueColorKey = other.mBlueColorKey;
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

void TexturedRectangle::SetColorKey(int red, int green, int blue) {

}