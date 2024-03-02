#include "Font.h"
#include "ResourceManager.h"
#include <iostream>

Font::Font(SDL_Renderer* render, const std::string& filepath, const std::string& str, int size, const SDL_Color& color)
	: mStr(str), mRect(), mFilepath(filepath), mRender(render), mColor(color) {
	mFont = ResourceManager::GetInstance().GetFont(filepath, size);
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), color);
	mTexture = SDL_CreateTextureFromSurface(render, ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

Font::Font(const Font& other)
:mRect(other.mRect), mTexture(other.mTexture), mFont(other.mFont), mStr(other.mStr), mFilepath(other.mFilepath), mRender(other.mRender), mColor(other.mColor)
{

}

Font& Font::operator=(const Font& other) {
	if (this != &other) {
		mRect = other.mRect;
		mTexture = other.mTexture;
		mFont = other.mFont;
		mStr = other.mStr;
		mFilepath = other.mFilepath;
		mRender = other.mRender;
		mColor = other.mColor;
	}
	return *this;
}

Font::~Font() {
	SDL_DestroyTexture(mTexture);
}

Font& Font::operator=(const std::string& str) {
	mStr = str;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(mRender, ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. (operator = font)" << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
	return *this;
}

void Font::SetText(const std::string& str) {
	mStr = str;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(mRender, ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. (settext() font)" << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

void Font::SetSize(int size) {
	mFont = ResourceManager::GetInstance().GetFont(mFilepath, size);
}

void Font::SetColor(SDL_Renderer* render, const SDL_Color& color) {
	mColor = color;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(render, ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. (setcolor() font)" << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

void Font::SetPosition(int x, int y) {
	int w, h;
	TTF_SizeUTF8(mFont, mStr.c_str(), &w, &h);

	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;
}

void Font::Render(SDL_Renderer* render) {
	SDL_RenderCopy(render, mTexture, NULL, &mRect);
}