#include "AnimatedSprite.h"
#include <iostream>


AnimatedSprite::AnimatedSprite(SDL_Renderer* render, const std::string& filepath, const ImageFormat& format): mDst(), mSrc(), mCountSpeed(0) {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance()->GetSurface(filepath, format);
	mTexture = SDL_CreateTextureFromSurface(render, retrieveSurface);
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

void AnimatedSprite::Render(SDL_Renderer*& render) {
	SDL_RenderCopyEx(render, mTexture, &mSrc, &mDst, mAngle, &mCenterPoint, mDirectionFlip);
}

void AnimatedSprite::SetPosition(int x, int y) {
	mDst.x = x;
	mDst.y = y;
}

void AnimatedSprite::MovePosition(int x, int y) {
	mDst.x += x;
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