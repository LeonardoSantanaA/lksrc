#include "Collider2D.h"

Collider2D::Collider2D(): mColliderRect() {
	mColliderRect.x = 0;
	mColliderRect.y = 0;
	mColliderRect.w = 0;
	mColliderRect.h = 0;
}

Collider2D::~Collider2D() {

}

SDL_bool Collider2D::IsColliding(const Collider2D& collider) {
	const SDL_Rect temp = collider.mColliderRect;
	return SDL_HasIntersection(&mColliderRect, &temp);
}

void Collider2D::SetAbsolutePosition(int x, int y) {
	mColliderRect.x = x;
	mColliderRect.y = y;
}

void Collider2D::SetAbsoluteDimensions(int w, int h) {
	mColliderRect.w = w;
	mColliderRect.h = h;
}