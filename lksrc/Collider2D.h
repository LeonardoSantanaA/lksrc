#pragma once

#include <SDL.h>

class Collider2D {
public:
	Collider2D();
	~Collider2D();

	SDL_bool IsColliding(const Collider2D& collider);
	void SetAbsolutePosition(int x, int y);
	void SetAbsoluteDimensions(int w, int h);

	void Update() {
		//not really needed...yet
	}

	void Render() {

	}

	inline SDL_Rect& GetColliderBoundingBox() { return mColliderRect; }

private:
	SDL_Rect mColliderRect;

};