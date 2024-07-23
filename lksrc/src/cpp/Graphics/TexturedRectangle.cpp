#include <iostream>
#include "Graphics/TexturedRectangle.h"
#include "Core/Engine.h"
#include "Camera/Camera.h"

TexturedRectangle::TexturedRectangle(const std::string& filepath, const ImageFormat& format, float scale)
: mRedColorKey(), mGreenColorKey(), mBlueColorKey(), mAngle(0), mDirectionFlip(SDL_FLIP_NONE){
	std::string newPath = filepath;
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance()->GetSurface(newPath, format);
	SDL_SetColorKey(retrieveSurface, SDL_FALSE, SDL_MapRGB(retrieveSurface->format, 0xFF, 0xFF, 0xFF));

	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), retrieveSurface); //copy the surface to texture
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}

	mRect.x = 0;
	mRect.y = 0;
	mRect.w = static_cast<int>(32 * scale);
	mRect.h = static_cast<int>(32 * scale);

	mCenterPoint.x = mRect.w / 2;
	mCenterPoint.y = mRect.h / 2;
}

TexturedRectangle::TexturedRectangle(const std::string& filepath, int redColorKey, int greenColorKey, int blueColorKey, const ImageFormat& format, float scale) {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance()->GetSurface(filepath, format);
	SDL_SetColorKey(retrieveSurface, SDL_TRUE, SDL_MapRGB(retrieveSurface->format, redColorKey, greenColorKey, blueColorKey));

	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), retrieveSurface); //copy the surface to texture
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

	mCenterPoint.x = mRect.w / 2;
	mCenterPoint.y = mRect.h / 2;
}

void TexturedRectangle::Init() {
	mRedColorKey = 0xFF;
	mGreenColorKey = 0xFF;
	mBlueColorKey = 0xFF;
}

TexturedRectangle::TexturedRectangle(const TexturedRectangle& other)
	:mRect(other.mRect), mTexture(other.mTexture), mRedColorKey(other.mRedColorKey), mGreenColorKey(other.mGreenColorKey), mBlueColorKey(other.mBlueColorKey), mAngle(other.mAngle), mCenterPoint(other.mCenterPoint), mDirectionFlip(other.mDirectionFlip) {
}

TexturedRectangle& TexturedRectangle::operator=(const TexturedRectangle& other) {
	if (this != &other) {
		mRect = other.mRect;
		mTexture = other.mTexture;
		mRedColorKey = other.mRedColorKey;
		mGreenColorKey = other.mGreenColorKey;
		mBlueColorKey = other.mBlueColorKey;
		mAngle = other.mAngle;
		mCenterPoint = other.mCenterPoint;
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

void TexturedRectangle::SetPosition(const Vec2D& vec) {
	mRect.x = static_cast<int>(vec.x);
	mRect.y = static_cast<int>(vec.y);
}

void TexturedRectangle::MovePosition(int x, int y) {
	mRect.x += x;
	mRect.y += y;
}

void TexturedRectangle::MovePosition(float x, float y) {
	mRect.x += static_cast<int>(x);
	mRect.y += static_cast<int>(y);
}

void TexturedRectangle::MovePosition(const Vec2D& vec) {
	mRect.x += static_cast<int>(vec.x);
	mRect.y += static_cast<int>(vec.y);
}

void TexturedRectangle::SetDimensions(int w, int h, float scale) {
	mRect.w = static_cast<int>(w * scale);
	mRect.h = static_cast<int>(h * scale);
}


void TexturedRectangle::Render() {
	Camera* camera = Camera::GetInstance();
	Vec2D cam = camera->GetPosition();
	SDL_Rect newDstRect = { (mRect.x - static_cast<int>(cam.x)) - static_cast<int>(camera->GetZoom()), (static_cast<int>(mRect.y) - static_cast<int>(cam.y) - static_cast<int>(camera->GetZoom())), mRect.w * static_cast<int>(camera->GetZoom()), mRect.h * static_cast<int>(camera->GetZoom()) };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), mTexture, nullptr, &newDstRect, mAngle, &mCenterPoint, mDirectionFlip);
}

void TexturedRectangle::FlipImageHorizontal() {
	if (mDirectionFlip == SDL_FLIP_NONE) {
		mDirectionFlip = SDL_FLIP_HORIZONTAL;
	}
	else {
		mDirectionFlip = SDL_FLIP_NONE;
	}
}

void TexturedRectangle::FlipImageVertical() {
	if (mDirectionFlip == SDL_FLIP_NONE) {
		mDirectionFlip = SDL_FLIP_VERTICAL;
	}
	else {
		mDirectionFlip = SDL_FLIP_NONE;
	}
}