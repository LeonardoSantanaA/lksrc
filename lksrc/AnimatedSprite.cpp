#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(SDL_Renderer* render, const std::string& filepath, const ImageFormat& format): mDst(), mSrc() {
	SDL_Surface* retrieveSurface = ResourceManager::GetInstance()->GetSurface(filepath, format);
	mTexture = SDL_CreateTextureFromSurface(render, retrieveSurface);
	SDL_FreeSurface(retrieveSurface);
}

AnimatedSprite::~AnimatedSprite() {
	SDL_DestroyTexture(mTexture);
}

void AnimatedSprite::Draw(int x, int y, int w, int h, float scale) {
	mDst.x = x;
	mDst.y = y;
	mDst.w = static_cast<int>(w * scale);
	mDst.h = static_cast<int>(h * scale);
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
	SDL_RenderCopy(render, mTexture, &mSrc, &mDst);
}