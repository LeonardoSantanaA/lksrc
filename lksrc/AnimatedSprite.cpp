#include "AnimatedSprite.h"
#include <iostream>
#include "Engine.h"
#include "Camera.h"


AnimatedSprite::AnimatedSprite(const std::string& filepath, const ImageFormat& format) : mDst(), mSrc(), mCountSpeed(0), mAngle(0), mCenterPoint(SDL_Point{ 0,0 }), mDirectionFlip(SDL_FLIP_NONE) {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance()->GetSurface(filepath, format);
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), retrieveSurface);
}

AnimatedSprite::~AnimatedSprite() {
	SDL_DestroyTexture(mTexture);
}

void AnimatedSprite::PlayFrame(int x, int y, int w, int h, int frame) {
	mSrc.x = x + w * frame;
	mSrc.y = y;
	mSrc.w = w;
	mSrc.h = h;
}

void AnimatedSprite::Update() {

}

void AnimatedSprite::Render() {
	Camera* camera = Camera::GetInstance();
	Vec2D cam = camera->GetPosition();
	SDL_Rect newDstRect = {(static_cast<int>((mDst.x - cam.x) * camera->GetZoom())), (static_cast<int>((mDst.y - cam.y) * camera->GetZoom())), static_cast<int>(mDst.w * camera->GetZoom()), static_cast<int>(mDst.h * camera->GetZoom()) };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), mTexture, &mSrc, &newDstRect, mAngle, &mCenterPoint, mDirectionFlip);
}

void AnimatedSprite::SetPosition(int x, int y) {
	mDst.x = x;
	mDst.y = y;
}

void AnimatedSprite::MovePosition(int x, int y) {
	mDst.x += x ;
	mDst.y += y;
}


void AnimatedSprite::SetDimensions(int w, int h, float scale) {
	mDst.w = static_cast<int>(w * scale);
	mDst.h = static_cast<int>(h * scale);
}

void AnimatedSprite::FlipImageHorizontal() {
	if (mDirectionFlip == SDL_FLIP_NONE) {
		mDirectionFlip = SDL_FLIP_HORIZONTAL;
	}
	else {
		mDirectionFlip = SDL_FLIP_NONE;
	}
}

void AnimatedSprite::FlipImageVertical() {
	if (mDirectionFlip == SDL_FLIP_NONE) {
		mDirectionFlip = SDL_FLIP_VERTICAL;
	}
	else {
		mDirectionFlip = SDL_FLIP_NONE;
	}
}