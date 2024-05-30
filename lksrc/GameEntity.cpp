#include "GameEntity.h"
#include "Collider2D.h"
#include "Engine.h"

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
	if (mnoptrSprite) {
		delete mnoptrSprite;
		mnoptrSprite = nullptr;
	}

	if (mnoptrAnimatedSprite) {
		delete mnoptrAnimatedSprite;
		mnoptrAnimatedSprite = nullptr;
	}

	if (mPoint) {
		delete mPoint;
		mPoint = nullptr;
	}

	for (size_t i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			delete mnoptrColliders[i];
			mnoptrColliders[i] = nullptr;
		}
	}
	
}

void GameEntity::Update() {
	if (mPoint) {
		mPoint->x = GetX() + GetWidth() / 2;
		mPoint->y = GetY() + GetHeight() / 2;
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
				//SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(), 255, 255, 255, SDL_ALPHA_OPAQUE);
				//SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), mnoptrColliders[i]->GetColliderBoundingBox());
			}
			else {
				std::cout << "trying access nullptr mnoptrcolliders, index: " << i << " gameentity::render()." << std::endl;
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

bool GameEntity::IsLastFrame() {
	if (mnoptrAnimatedSprite) {
		auto search = mAnimations.find(mCurrentAnimationName);
		if (search != mAnimations.end()) {

			if (mFrame+1 >= mAnimations[mCurrentAnimationName].second) {
				
				return true;
			}
		
			return false;

		}
	}
	std::cout << "trying get nullptr in gameentity::islastframe()" << std::endl;
	return false;
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(filepath, format, scale);
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(filepath, red, green, blue, format, scale);
}

void GameEntity::AddAnimatedSprite(const std::string& filepath, const ImageFormat& format) {
	mnoptrAnimatedSprite = new AnimatedSprite(filepath, format);
}


void GameEntity::AddCollider2D() {
	mnoptrColliders.push_back(new Collider2D());
}

void GameEntity::AddPoint() {
	if (!mPoint) {
		float x = GetX() + GetWidth() / 2;
		float y = GetY() + GetHeight() / 2;
		mPoint = new Point(x, y);
	}
}

SDL_bool GameEntity::IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex) {
	if (mnoptrColliders[index] && otherEntity.mnoptrColliders[otherIndex]) {
		return this->GetCollider2D(index)->IsColliding(*otherEntity.mnoptrColliders[otherIndex]);
	}
	std::cout << "mcollider nullptr, index: " << index << " other index: " << otherIndex << ". gameentity::iscolliding()." << std::endl;
	return SDL_FALSE;
}

void GameEntity::SetOffsetPositionCollision(int indexCollision, int xoffsetCollision, int yoffsetCollision) {
	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (i == indexCollision && mnoptrColliders[i]) {
			mnoptrColliders[i]->SetXOffset(xoffsetCollision);
			mnoptrColliders[i]->SetYOffset(yoffsetCollision);
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
		std::cout << "trying access a null pointer. gameentity::SetPosition()." << std::endl;
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->SetPosition(x, y);
			
		}
		else {
			std::cout << "trying access a null pointer. gameentity::setposition(). index " << i << "." << std::endl;
		}
	}
}

void GameEntity::MovePosition(int x, int y) {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->MovePosition(x, y);
	}else if (mnoptrSprite) {
		mnoptrSprite->MovePosition(x, y);
	}else {
		std::cout << "trying access a null pointer. SetPosition()." << std::endl;
	}

	for (int i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			mnoptrColliders[i]->MovePosition(x, y);
		}
		else {
			std::cout << "trying access a null pointer. gameentity::moveposition(). index " << i << "." << std::endl;
		}
	}
}

void GameEntity::SetDimensions(int w, int h, float scale) {
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetDimensions(w, h, scale);
	}else {
	std::cout << "trying access a null pointer. SetPosition()." << std::endl;
	}

	if (mnoptrSprite) {
		mnoptrSprite->SetDimensions(w, h, scale);
	}else {
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
	std::cout << "trying access a nullptr. gameentity::gettexturedrectangle()." << std::endl;
	
}

Collider2D* GameEntity::GetCollider2D(size_t index) {
	if (mnoptrColliders[index]) {
		return mnoptrColliders[index];
	}
	std::cout << "trying access a nullptr. gameentity::getcollider2D(), index: " << index << std::endl;
	return nullptr;
}

int GameEntity::GetX() { 
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetX();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetX(); 
	}
	 
	std::cout << "gameentity::getx() from nullptr sprite." << std::endl;  
	return -1; 
}

int GameEntity::GetY() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetY();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetY(); 
	}
	 
	std::cout << "gameentity::gety() from nullptr sprite." << std::endl; 
	return -1; 
}

int GameEntity::GetWidth() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetWidth();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetWidth(); 
	}
	 
	std::cout << "gameentity::getwidth() from nullptr sprite." << std::endl;  
	return -1; 
}

int GameEntity::GetHeight() {
	if (mnoptrAnimatedSprite) {
		return mnoptrAnimatedSprite->GetHeight();
	}else if (mnoptrSprite) {
		return mnoptrSprite->GetHeight(); 
	}
	 
	std::cout << "gameentity::getheight() from nullptr sprite." << std::endl;  
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
		std::cout << "gameentity::setanglerotate() from nullptr sprite." << std::endl;
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
		std::cout << "gameentity::setcenterpointrotate() from nullptr sprite." << std::endl;
	}

	
	
}

void GameEntity::FlipHorizontal() { 
	
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->FlipImageHorizontal();
	}else if (mnoptrSprite) {
		mnoptrSprite->FlipImageHorizontal();
	}
	else {
		std::cout << "gameentity::fliphorizontal() from nullptr sprite." << std::endl;
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
		std::cout << "gameentity::flipvertical() from nullptr sprite." << std::endl;
	}

	
}