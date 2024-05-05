#include "Collider2D.h"

#include <iostream>
#include "Engine.h"
#include "Camera.h"

Collider2D::Collider2D(): mnoptrColliderRect() {
	mnoptrColliderRect = new SDL_Rect;
	mnoptrColliderRect->x = 0;
	mnoptrColliderRect->y = 0;
	mnoptrColliderRect->w = 0;
	mnoptrColliderRect->h = 0;
    xOffset = 0;
    yOffset = 0;
}

Collider2D::~Collider2D() {
	if (mnoptrColliderRect) {
		delete mnoptrColliderRect;
	}
}

SDL_bool Collider2D::IsColliding(const Collider2D& collider) {
	if (mnoptrColliderRect) {
		const SDL_Rect* temp = collider.mnoptrColliderRect;
		if (temp) {
			return SDL_HasIntersection(mnoptrColliderRect, temp);
		}
		else {
			std::cout << "trying intersects with a nullptr. collider2d::iscolliding()." << std::endl;
		}
	}
	else {
		std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::iscolliuding()." << std::endl;
	}
	return SDL_FALSE;
}

void Collider2D::SetPosition(int x, int y) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->x = x + xOffset;
       // std::cout << "offset do x: " << xOffset << std::endl;
        mnoptrColliderRect->y = y + yOffset;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::setposition()." << std::endl;
    }
}

void Collider2D::MovePosition(int x, int y) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->x += (x);
        mnoptrColliderRect->y += (y);
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::moveposition()." << std::endl;
    }
}

void Collider2D::SetDimensions(int w, int h) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->w = w;
        mnoptrColliderRect->h = h;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::setdimensions()." << std::endl;
    }
}

int Collider2D::GetWidth() {
    if (mnoptrColliderRect) {
        return mnoptrColliderRect->w;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::hetwidth()." << std::endl;
    }
}

int Collider2D::GetHeight() {
    if (mnoptrColliderRect) {
        return mnoptrColliderRect->h;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::hetheight()." << std::endl;
    }
}

void Collider2D::Render() {
    Vec2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect newDstRect = { mnoptrColliderRect->x - cam.x, mnoptrColliderRect->y - cam.y, mnoptrColliderRect->w, mnoptrColliderRect->h };
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &newDstRect);
}
