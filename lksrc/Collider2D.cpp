#include "Collider2D.h"

#include <iostream>

Collider2D::Collider2D(): mnoptrColliderRect() {
	mnoptrColliderRect = new SDL_Rect;
	mnoptrColliderRect->x = 0;
	mnoptrColliderRect->y = 0;
	mnoptrColliderRect->w = 0;
	mnoptrColliderRect->h = 0;
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
        mnoptrColliderRect->x = x;
        mnoptrColliderRect->y = y;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::setposition()." << std::endl;
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

