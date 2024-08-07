#pragma once

#include <string>
#include <SDL.h>
#include "Managers/ResourceManager.h"

class AnimatedSprite {
public:
	AnimatedSprite(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);
	~AnimatedSprite();

	void PlayFrame(int x, int y, int w, int h, int frame);

	void Update();
	void Render();

	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
	void MovePosition(float x, float y);
	void SetDimensions(int w, int h, float scale);

	inline int GetX() const { return mDst.x; }
	inline int GetY() const { return mDst.y; }
	inline int GetWidth() const { return mDst.w; }
	inline int GetHeight() const { return mDst.h; }

	inline void SetAngle(float angle) { mAngle = angle; }
	inline void SetCenterPointRotate(SDL_Point point) { mCenterPoint = point; }
	inline void SetCountSpeed(float speed) { mCountSpeed = speed; }

	void FlipImageHorizontal();
	void FlipImageVertical();

private:
	float mCountSpeed;
	SDL_Rect mSrc;	//where we're selecting from
	SDL_Rect mDst;	//where we're rendering
	SDL_Texture* mTexture;
	float mAngle;
	SDL_Point mCenterPoint;
	SDL_RendererFlip mDirectionFlip;
};