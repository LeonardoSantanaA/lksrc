#include "GameEntity.h"
#include "Collider2D.h"

GameEntity::GameEntity() {
	mnoptrSprite = nullptr;
	mRender = nullptr;
	mnoptrCollider = nullptr;
	mDebugMode = false;
}

GameEntity::GameEntity(SDL_Renderer* render, const std::string& spritepath, const ImageFormat& format, float scale) {
	mDebugMode = false;
	mRender = render;
	mnoptrSprite = new TexturedRectangle(mRender, spritepath, format, scale);
	mnoptrCollider = new Collider2D();
}

GameEntity::~GameEntity() {
	delete mnoptrSprite;
	delete mnoptrCollider;
}

void GameEntity::Update() {
	if (mnoptrCollider) {
		mnoptrCollider->SetAbsolutePosition(this->GetX(), this->GetY());
		mnoptrCollider->SetAbsoluteDimensions(this->GetWidth(), this->GetHeight());
	}

}

void GameEntity::Render() {
	if (mnoptrSprite) {
		mnoptrSprite->Render(mRender);
	}
	if (mnoptrCollider && mDebugMode) {
		SDL_SetRenderDrawColor(mRender, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(mRender, &mnoptrCollider->GetColliderBoundingBox());
	}

}

SDL_bool GameEntity::IsColliding(const GameEntity& otherEntity) {
	if (mnoptrCollider) {
		return this->GetCollider2D().IsColliding(*otherEntity.mnoptrCollider);
	}
	std::cout << "mcollider nullptr. gameentity::IsColliding()." << std::endl;
	return SDL_FALSE;
}

