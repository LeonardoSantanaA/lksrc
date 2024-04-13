#pragma once

#include "GlobalResources.h"
#include <iostream>

#include <SDL.h>

class ICollider2D {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class Collider2D : public ICollider2D {
public:
	Collider2D();
	~Collider2D();

	SDL_bool IsColliding(const Collider2D& collider);
	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
	void SetDimensions(int w, int h);

	int GetWidth();
	int GetHeight();

	void Update() { //not really needed... 
	}

	void Render() {}

	inline SDL_Rect* GetColliderBoundingBox() { return mnoptrColliderRect; }
	inline void SetXOffset(int x) { xOffset = x; std::cout << "setado para: " << xOffset << std::endl; }
	inline void SetYOffset(int y) { yOffset = y; }


private:
	SDL_Rect* mnoptrColliderRect;
	int xOffset;
	int yOffset;
};