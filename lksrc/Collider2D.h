#pragma once

#include "GlobalResources.h"

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


private:
	SDL_Rect* mnoptrColliderRect;

};