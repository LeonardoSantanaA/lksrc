#pragma once

#include <iostream>

#include <SDL.h>
#include "Core/GlobalResources.h"

class ICollider2D {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class Collider2D : public ICollider2D {
public:
	Collider2D();
	~Collider2D();

	//return if is colliding with another collider
	SDL_bool IsColliding(const Collider2D& collider);
	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
	void MovePosition(float x, float y);
	void SetDimensions(int w, int h, float scale = SCALE);

	int GetWidth();
	int GetHeight();

	void Update() { //not really needed... 
	}

	void Render();

	inline SDL_Rect* GetColliderBoundingBox() { return mnoptrColliderRect; }
	inline void SetXOffset(int x) { xOffset = static_cast<float>(x); }
	inline void SetYOffset(int y) { yOffset = static_cast<float>(y); }
	inline void SetXOffset(float x) { xOffset = x; }
	inline void SetYOffset(float y) { yOffset = y; }


private:
	SDL_Rect* mnoptrColliderRect;
	float xOffset;
	float yOffset;
};