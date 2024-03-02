#pragma once

#include "TexturedRectangle.h"
//#include "Collider2D.h"

class Collider2D;

class GameEntity {
public:
	GameEntity();

	GameEntity(SDL_Renderer* render, const std::string& spritepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	~GameEntity();

	void Update();

	void Render();

	inline TexturedRectangle& GetTexturedRectangle() const{
		if (mnoptrSprite) {
			return *mnoptrSprite;
		}
		std::cout << "trying access a null pointer. GetTexturedRectangle()." << std::endl;
	}

	inline int GetX() { if (mnoptrSprite) { return mnoptrSprite->GetX(); } std::cout << "getx() from nullptr sprite." << std::endl;  return -1; }
	inline int GetY() { if (mnoptrSprite) { return mnoptrSprite->GetY(); } std::cout << "gety() from nullptr sprite." << std::endl;  return -1; }
	inline int GetWidth() { if (mnoptrSprite) { return mnoptrSprite->GetWidth(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }
	inline int GetHeight() { if (mnoptrSprite) { return mnoptrSprite->GetHeight(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }

	inline void SetPosition(int x, int y) {
		if (mnoptrSprite) {
			mnoptrSprite->SetPosition(x, y);
		}
		else {
			std::cout << "trying access a null pointer. SetPosition()." << std::endl;
		}
		
	}

	inline void SetDimensions(int w, int h, float scale = SCALE) {
		if (mnoptrSprite) {
			mnoptrSprite->SetDimensions(w, h, scale);
		}
		else {
			std::cout << "trying access a null pointer. SetPosition()." << std::endl;
		}
	}

	inline Collider2D& GetCollider2D() { return *mnoptrCollider; }
	inline void SetDebugMode(bool debugMode) { mDebugMode = debugMode; }

	SDL_bool IsColliding(const GameEntity& otherEntity);

private:
	TexturedRectangle* mnoptrSprite;
	Collider2D* mnoptrCollider;
	SDL_Renderer* mRender;

	bool mDebugMode;
};