#pragma once

#include <SDL.h>

class Collider2D {
public:
	Collider2D();
	~Collider2D();

	SDL_bool IsColliding(const Collider2D& collider);
	void SetPosition(int x, int y);
	void SetDimensions(int w, int h);

	void Update() {
		//not really needed...yet
	}

	void Render() {

	}

	inline SDL_Rect* GetColliderBoundingBox() { return mnoptrColliderRect; }

private:
	SDL_Rect* mnoptrColliderRect;

};