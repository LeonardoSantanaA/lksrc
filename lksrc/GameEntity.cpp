#include "GameEntity.h"
#include "Collider2D.h"

GameEntity::GameEntity() {
	mnoptrSprite = nullptr;
	mRender = nullptr;
	mDebugMode = false;
}

GameEntity::GameEntity(SDL_Renderer* render) {
	mnoptrSprite = nullptr;
	mRender = render;
	mDebugMode = false;
}

/*
GameEntity::GameEntity(SDL_Renderer* render, const std::string& spritepath, const ImageFormat& format, float scale) {
	mDebugMode = false;
	mRender = render;

	mnoptrCollider = new Collider2D();
}
*/

GameEntity::~GameEntity() {
	if (mnoptrSprite) {
		delete mnoptrSprite;
	}

	for (size_t i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			delete mnoptrColliders[i];
		}
	}
	
}

void GameEntity::Update() {
	

}

void GameEntity::Render() {
	if (mnoptrSprite) {
		mnoptrSprite->Render(mRender);
	}

	if (mDebugMode) {
		for (size_t i = 0; i < mnoptrColliders.size(); ++i) {
			if (mnoptrColliders[i]) {
				SDL_SetRenderDrawColor(mRender, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(mRender, mnoptrColliders[i]->GetColliderBoundingBox());
			}
			else {
				std::cout << "trying access nullptr mnoptrcolliders, index: " << i << " gameentity::render()." << std::endl;
			}
		}	
	}

}

void GameEntity::AddTexturedRectangleComponent(std::string filepath, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(mRender, filepath, format, scale);
}

void GameEntity::AddTexturedRectangleComponent(std::string filepath, int red, int green, int blue, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(mRender, filepath, red, green, blue, format, scale);
}

void GameEntity::AddCollider2D() {
	mnoptrColliders.push_back(new Collider2D());
}

SDL_bool GameEntity::IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex) {
	if (mnoptrColliders[index] && otherEntity.mnoptrColliders[otherIndex]) {
		return this->GetCollider2D(index)->IsColliding(*otherEntity.mnoptrColliders[otherIndex]);
	}
	std::cout << "mcollider nullptr, index: " << index << " other index: " << otherIndex << ". gameentity::iscolliding()." << std::endl;
	return SDL_FALSE;
}

void GameEntity::SetPosition(int x, int y, int indexCollision, int xoffsetCollision, int yoffsetCollision) {
	if (mnoptrSprite) {
		mnoptrSprite->SetPosition(x, y);
	}
	else {
		std::cout << "trying access a null pointer. SetPosition()." << std::endl;
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->SetPosition(x, y);
			if (i == indexCollision) {
				mnoptrColliders[i]->SetPosition(x + xoffsetCollision, y + yoffsetCollision);
			}
		}
		else {
			std::cout << "trying access a null pointer. gameentity::setposition(). index " << i << "." << std::endl;
		}
	}
}

void GameEntity::SetDimensions(int w, int h, float scale) {
	if (mnoptrSprite) {
		mnoptrSprite->SetDimensions(w, h, scale);
	}
	else {
		std::cout << "trying access a null pointer. SetPosition()." << std::endl;
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->SetDimensions(w, h);
		}
		else {
			std::cout << "trying access a null pointer. gameentity::setdimensions(). index " << i << "." << std::endl;
		}
	}
}