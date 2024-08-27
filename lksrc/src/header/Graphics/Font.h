#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Font {
public:
	Font(const std::string& filepath, const std::string& str, int size, const SDL_Color& color = {255, 255, 255});
	Font(const Font& other);
	Font& operator=(const Font& other);
	~Font();

	Font& operator=(const std::string& str);

	void SetText(const std::string& str);
	void SetSize(int size);
	void SetColor(const SDL_Color& color);
	void SetPosition(int x, int y);
	int GetSize();
	void Render();
	void SetWrapLimitSize(int limitWrap);

private:
	SDL_Rect mRect;
	SDL_Texture* mTexture;
	TTF_Font* mFont;
	SDL_Color mColor;
	std::string mStr;
	std::string mFilepath;
	int mWidth, mHeight;

	void UpdateDimensions();
};