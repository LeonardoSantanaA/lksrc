#include <iostream>
#include "Collision/Collider2D.h"
#include "Core/Engine.h"
#include "Camera/Camera.h"

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
        mnoptrColliderRect->x = x + static_cast<int>(xOffset);
        mnoptrColliderRect->y = y + static_cast<int>(yOffset);
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::setposition()." << std::endl;
    }
}

void Collider2D::MovePosition(int x, int y) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->x += x;
        mnoptrColliderRect->y += y;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::moveposition()." << std::endl;
    }
}

void Collider2D::MovePosition(float x, float y) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->x += static_cast<int>(x);
        mnoptrColliderRect->y += static_cast<int>(y);
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::moveposition()." << std::endl;
    }
}

void Collider2D::SetDimensions(int w, int h, float scale) {
    if (mnoptrColliderRect) {
        mnoptrColliderRect->w = w * scale;
        mnoptrColliderRect->h = h * scale;
    }
    else {
        std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::setdimensions()." << std::endl;
    }
}

int Collider2D::GetWidth() {
    if (mnoptrColliderRect) {
        return mnoptrColliderRect->w;
    }
    
     std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::hetwidth()." << std::endl;
     return 0;
}

int Collider2D::GetHeight() {
    if (mnoptrColliderRect) {
        return mnoptrColliderRect->h;
    }
  
    std::cout << "trying access nullptr mnoptrcolliderrect. collider2d::hetheight()." << std::endl;
    return 0;
    
}

void Collider2D::Render() {
    Camera* camera = Camera::GetInstance();
    Vec2D cam = camera->GetPosition();
    SDL_Rect newDstRect = { static_cast<int>((mnoptrColliderRect->x - cam.x) * camera->GetZoom()), static_cast<int>((mnoptrColliderRect->y - cam.y) * camera->GetZoom()), 
        static_cast<int>(mnoptrColliderRect->w * camera->GetZoom()), static_cast<int>(mnoptrColliderRect->h * camera->GetZoom())};
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &newDstRect);
}
