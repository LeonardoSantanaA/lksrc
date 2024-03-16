#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Font {
public:
	Font(SDL_Renderer* render, const std::string& filepath, const std::string& str, int size, const SDL_Color& color = {255, 255, 255});
	Font(const Font& other);
	Font& operator=(const Font& other);
	~Font();

	Font& operator=(const std::string& str);

	void SetText(const std::string& str);
	void SetSize(int size);
	void SetColor(SDL_Renderer* render, const SDL_Color& color);
	void SetPosition(int x, int y);
	void Render(SDL_Renderer* render);

private:
	SDL_Rect mRect;
	SDL_Texture* mTexture;
	SDL_Renderer* mRender;
	TTF_Font* mFont;
	SDL_Color mColor;
	std::string mStr;
	std::string mFilepath;
	int mWidth, mHeight;

	void UpdateDimensions();
};