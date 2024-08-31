#include "Managers/GameEntity.h"
#include "Collision/Collider2D.h"
#include "Core/Engine.h"

GameEntity::GameEntity() {
	mnoptrSprite = nullptr;
	mnoptrAnimatedSprite = nullptr;
	mPoint = nullptr;
	mDebugMode = false;
	mAngle = 0;
	mCenterPoint = {};
	mFrame = 0;
	mAnimatedSpriteWidth = 0;
	mAnimatedSpriteHeight = 0;
	mAnimationSpeed = 1.0f;
	mLoop = false;
	mAnimationDelayCount = 0;
	mRenderLayer = RenderEntityLayer::END;
	AddPoint();
}

GameEntity::GameEntity(const std::string& name) {
	mName = name;
	mnoptrSprite = nullptr;
	mnoptrAnimatedSprite = nullptr;
	mPoint = nullptr;
	mDebugMode = false;
	mAngle = 0;
	mCenterPoint = {};
	mFrame = 0;
	mAnimatedSpriteWidth = 0;
	mAnimatedSpriteHeight = 0;
	mAnimationSpeed = 1.0f;
	mLoop = false;
	mAnimationDelayCount = 0;
	mRenderLayer = RenderEntityLayer::END;
	AddPoint();
}

GameEntity::~GameEntity() {
	mnoptrColliders.clear();
}

void GameEntity::Update() {
	if (mPoint) {
		mPoint->x = static_cast<float>(GetX() + GetWidth() / 2);
		mPoint->y = static_cast<float>(GetY() + GetHeight() / 2);
	}
}

void GameEntity::Render() {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->Render();
	}else if (mnoptrSprite) {
		mnoptrSprite->Render();
	} 

	if (mDebugMode) {
		for (size_t i = 0; i < mnoptrColliders.size(); ++i) {
			if (mnoptrColliders[i]) {
				mnoptrColliders[i]->Render();
			}
			else {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access nullptr mnoptrcolliders, index: %d GameEntity::Render()", static_cast<int>(i));
			}
		}	
	}

}

void GameEntity::UpdateSpriteSheet() {
	if (mnoptrAnimatedSprite) {
		auto search = mAnimations.find(mCurrentAnimationName);

		if (search != mAnimations.end()) {
			mnoptrAnimatedSprite->PlayFrame(0, mAnimations[mCurrentAnimationName].first, mAnimatedSpriteWidth, mAnimatedSpriteHeight, mFrame);

			if (mAnimationDelayCount < mAnimationSpeed) {
				mAnimationDelayCount++;
				
			}
			else {
				if (mFrame < mAnimations[mCurrentAnimationName].second) {
					mAnimationDelayCount = 0;
					mFrame++;
				}
				
				
			}
			if (mLoop && mFrame >= mAnimations[mCurrentAnimationName].second) {
				mFrame = 0;
				mAnimationDelayCount = 0;
			}
		}
	}
}

int GameEntity::GetCurrentAnimationFrame() const{
	return mFrame;
}

bool GameEntity::IsLastFrame() {
	if (mnoptrAnimatedSprite && this) {
		auto search = mAnimations.find(mCurrentAnimationName);
		if (search != mAnimations.end()) {
			if (mFrame + 1 >= mAnimations[mCurrentAnimationName].second) {
				return true;
			}
		
			return false;

		}
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying get nullptr in GameEntity::IsLastFrame()");
	return false;
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format, float scale) {
	mnoptrSprite = std::make_unique<TexturedRectangle>(filepath, format, scale);
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format, float scale) {
	mnoptrSprite = std::make_unique < TexturedRectangle>(filepath, red, green, blue, format, scale);
}

void GameEntity::AddAnimatedSprite(const std::string& filepath, const ImageFormat& format) {
	mnoptrAnimatedSprite =  std::make_unique<AnimatedSprite>(filepath, format);
}


void GameEntity::AddCollider2D() {
	mnoptrColliders.push_back(std::make_unique<Collider2D>());
}

void GameEntity::AddPoint() {
	if (!mPoint) {
		float x = GetX() + GetWidth() / static_cast<float>(2);
		float y = GetY() + GetHeight() / static_cast<float>(2);
		mPoint = std::make_unique<Point>(x, y);
	}
}

SDL_bool GameEntity::IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex) {
	if (mnoptrColliders[index] && otherEntity.mnoptrColliders[otherIndex]) {
		return this->GetCollider2D(index)->IsColliding(*otherEntity.mnoptrColliders[otherIndex]);
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "mCollider nullptr index: %d, other index: %d. GameEntity::IsColliding()", static_cast<int>(index), static_cast<int>(otherIndex));
	return SDL_FALSE;
}

void GameEntity::SetOffsetPositionCollision(int indexCollision, int xoffsetCollision, int yoffsetCollision, float scale) {
	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (i == indexCollision && mnoptrColliders[i]) {
			mnoptrColliders[i]->SetXOffset(xoffsetCollision * scale);
			mnoptrColliders[i]->SetYOffset(yoffsetCollision * scale);
			break;
		}
	}
}

void GameEntity::SetPosition(int x, int y) {
	if (mnoptrSprite) {
		mnoptrSprite->SetPosition(x, y);
	}
	else if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetPosition(x, y);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::SetPosition().");
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->SetPosition(x, y);
			
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. gameentity::setposition(). index %d", i);
		}
	}
}

void GameEntity::MovePosition(int x, int y) {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->MovePosition(x, y);
	}else if (mnoptrSprite) {
		mnoptrSprite->MovePosition(x, y);
	}else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::SetPosition().");
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->MovePosition(x, y);
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::MovePosition(). index %d.", i);
		}
	}
}

void GameEntity::MovePosition(float x, float y) {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->MovePosition(x, y);
	}
	else if (mnoptrSprite) {
		mnoptrSprite->MovePosition(x, y);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::SetPosition().");
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->MovePosition(x, y);
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer collider. GameEntity::MovePosition(). index %d.", i);
		}
	}
}


void GameEntity::SetDimensions(int w, int h, float scale) {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetDimensions(w, h, scale);
	}else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::SetDimensions().");
	}

	if (mnoptrSprite) {
		mnoptrSprite->SetDimensions(w, h, scale);
	}else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer. GameEntity::SetPosition().");
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->SetDimensions(w, h);
		} 
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a null pointer collider. GameEntity::SetDimensions(). index %d.", i);
		}
	}
}

void GameEntity::AddAnimation(const std::string& animationName, int yStartPositionInSpritesheet, int numberFrames) {
	mAnimations.insert(std::make_pair(animationName, std::make_pair(yStartPositionInSpritesheet, numberFrames)));
}

void GameEntity::ChangeAnimation(const std::string& animationName) {
	if (mCurrentAnimationName != animationName) {
		mFrame = 0;
		mCurrentAnimationName = animationName;
		mAnimationDelayCount = 0;
		if (mnoptrAnimatedSprite) {
			mnoptrAnimatedSprite->SetCountSpeed(0.0f);
		}
	}

}

std::string GameEntity::GetCurrentAnimation() const {
	return mCurrentAnimationName;
}

TexturedRectangle& GameEntity::GetTexturedRectangle() const {
	if (mnoptrSprite) {
		return *mnoptrSprite;
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a nullptr. GameEntity::GetTexturedRectangle().");
}

Collider2D* GameEntity::GetCollider2D(size_t index) {
	if (mnoptrColliders[index]) {
		return mnoptrColliders[index].get();
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "trying access a nullptr. GameEntity::getcollider2D(), index: %d", static_cast<int>(index));
	return nullptr;
}

int GameEntity::GetX() { 
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetX();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetX(); 
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::GetX() from nullptr sprite.");
 
	return -1; 
}

int GameEntity::GetY() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetY();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetY(); 
	}
	 
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::GetY() from nullptr sprite.");
	return -1; 
}

int GameEntity::GetWidth() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetWidth();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetWidth(); 
	}
	 
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::GetWidth() from nullptr sprite.");
	return -1; 
}

int GameEntity::GetHeight() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetHeight();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetHeight(); 
	}
	 
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::GetHeight() from nullptr sprite.");
	return -1; 
}


void GameEntity::SetAngleRotate(float angle) { 
	mAngle = angle;
	if (mnoptrSprite) {
		mnoptrSprite->SetAngle(angle);
	}
	else if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetAngle(angle);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::SetAngleRotate() from nullptr sprite.");
	}
	
	
}

void GameEntity::SetCenterPointRotate(const SDL_Point& point) { 
	mCenterPoint = point;

	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetCenterPointRotate(point);
	}
	else if (mnoptrSprite) {
		mnoptrSprite->SetCenterPointRotate(point);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::SetCenterPointRotate() from nullptr sprite.");
	}
}

void GameEntity::FlipHorizontal() { 
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->FlipImageHorizontal();
	}else if (mnoptrSprite) {
		mnoptrSprite->FlipImageHorizontal();
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::FlipHorizontal() from nullptr sprite.");
	}
}

void GameEntity::FlipVertical() { 
	if (mnoptrSprite) {
		mnoptrSprite->FlipImageVertical();
	}
	else if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->FlipImageVertical();
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameEntity::FlipVertical() from nullptr sprite.");
	}
	
}