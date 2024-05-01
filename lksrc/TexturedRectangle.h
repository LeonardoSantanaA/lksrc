#pragma once

#include <iostream>
#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GlobalResources.h"
#include "Vec2D.h"

class TexturedRectangle {
public:
	TexturedRectangle(const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	TexturedRectangle(const std::string& filepath, int redColorKey, int greenColorKey, int blueColorKey, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	void Init();
	TexturedRectangle(const TexturedRectangle& other);
	TexturedRectangle& operator=(const TexturedRectangle& other);
	~TexturedRectangle();

	void Update();
	void SetPosition(int x, int y);
	void SetPosition(const Vec2D& vec);
	void MovePosition(int x, int y);
	void MovePosition(const Vec2D& vec);
	void SetDimensions(int w, int h, float scale = SCALE);
	void Render();

	inline int GetX() const { return mRect.x; }
	inline int GetY() const { return mRect.y; }
	inline int GetWidth() const { return mRect.w; }
	inline int GetHeight() const { return mRect.h; }
	inline void SetAngle(float angle) { mAngle = angle; }
	inline void SetCenterPointRotate(SDL_Point point) { mCenterPoint = point; }

	void FlipImageHorizontal();
	void FlipImageVertical();


private:
	inline SDL_Rect GetRectangle() const { return mRect; }

	SDL_Rect mRect;
	SDL_Texture* mTexture;

	int mRedColorKey;
	int mGreenColorKey;
	int mBlueColorKey;

	float mAngle;
	SDL_Point mCenterPoint;
	SDL_RendererFlip mDirectionFlip;
};