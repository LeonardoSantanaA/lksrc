#include "Core/Engine.h"
#include "Graphics/Font.h"
#include "Managers/ResourceManager.h"
#include <iostream>


Font::Font(const std::string& filepath, const std::string& str, int size, const SDL_Color& color)
	: mStr(str), mRect(), mFilepath(filepath), mColor(color), mWidth(0), mHeight(0) {
	mFont = ResourceManager::GetInstance()->GetFont(filepath, size);

	SDL_Surface* ttfSurface = TTF_RenderUTF8_Blended_Wrapped(mFont, mStr.c_str(), color, Engine::GetInstance()->GetWidth());
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface." << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

Font::Font(const Font& other)
:mRect(other.mRect), mTexture(other.mTexture), mFont(other.mFont), mStr(other.mStr), mFilepath(other.mFilepath), mColor(other.mColor), mWidth(other.mWidth), mHeight(other.mHeight)
{

}

Font& Font::operator=(const Font& other) {
	if (this != &other) {
		mRect = other.mRect;
		mTexture = other.mTexture;
		mFont = other.mFont;
		mStr = other.mStr;
		mFilepath = other.mFilepath;
		mColor = other.mColor;
		mWidth = other.mWidth;
		mHeight = other.mHeight;
	}
	return *this;
}

Font::~Font() {
	SDL_DestroyTexture(mTexture);
}

Font& Font::operator=(const std::string& str) {
	mStr = str;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. font::operator =" << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
	UpdateDimensions();
	return *this;
}

void Font::SetWrapLimitSize(int limitWrap) {
	SDL_Surface* ttfSurface = TTF_RenderUTF8_Blended_Wrapped(mFont, mStr.c_str(), mColor, limitWrap);
	//mTexture = nullptr;
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt set wrap from surface." << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

void Font::SetText(const std::string& str) {
	mStr = str;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. font::settext()/" << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
	UpdateDimensions();
}

void Font::SetSize(int size) {
	mFont = ResourceManager::GetInstance()->GetFont(mFilepath, size);
}

void Font::SetColor(const SDL_Color& color) {
	mColor = color;
	SDL_Surface* ttfSurface = TTF_RenderText_Solid(mFont, mStr.c_str(), mColor);
	mTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), ttfSurface);
	if (mTexture == NULL) {
		std::cout << "Couldnt create texture from surface. font::setcolor()." << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(ttfSurface);
}

void Font::SetPosition(int x, int y) {
	int w, h;
	TTF_SizeUTF8(mFont, mStr.c_str(), &w, &h);

	mRect.x = x;
	mRect.y = y;
	
	UpdateDimensions();
}

int Font::GetSize() {
	if (mFont) {
		int w = 0, h = 0;
		TTF_SizeText(mFont, mStr.c_str(), &w, &h);
		return w;
	}
	return 0;
}

void Font::Render() {
	SDL_RenderCopy(Engine::GetInstance()->GetRender(), mTexture, NULL, &mRect);

}

void Font::UpdateDimensions() {
	int w, h;
	TTF_SizeUTF8(mFont, mStr.c_str(), &w, &h);
	mWidth = w;
	mHeight = h;
	mRect.w = mWidth;
	mRect.h = mHeight;
}