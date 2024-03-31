#include "GameEntity.h"
#include "Collider2D.h"

GameEntity::GameEntity() {
	mnoptrSprite = nullptr;
	mnoptrAnimatedSprite = nullptr;
	mRender = nullptr;
	mDebugMode = false;
	mLayer = {};
	mAngle = 0;
	mCenterPoint = {};
	mFrame = 0;
	mAnimatedSpriteWidth = 0;
	mAnimatedSpriteHeight = 0;
	mAnimationSpeed = 1.0f;
	mLoop = false;
	mAnimationDelayCount = 0;
}

GameEntity::GameEntity(const std::string& name, SDL_Renderer* render) {
	mName = name;
	mnoptrSprite = nullptr;
	mnoptrAnimatedSprite = nullptr;
	mRender = render;
	mDebugMode = false;
	mLayer = {};
	mAngle = 0;
	mCenterPoint = {};
	mFrame = 0;
	mAnimatedSpriteWidth = 0;
	mAnimatedSpriteHeight = 0;
	mAnimationSpeed = 1.0f;
	mLoop = false;
	mAnimationDelayCount = 0;
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

	for (size_t i = 0; i < mnoptrColliders.size(); ++i) {
		if (mnoptrColliders[i]) {
			delete mnoptrColliders[i];
			mnoptrColliders[i] = nullptr;
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
					std::cout << "passar frame!" << std::endl;
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

void GameEntity::Render(const std::string& animationName, bool loop, float speed) {
	mnoptrAnimatedSprite->Render(mRender);
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(mRender, filepath, format, scale);
}

void GameEntity::AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format, float scale) {
	mnoptrSprite = new TexturedRectangle(mRender, filepath, red, green, blue, format, scale);
}

void GameEntity::AddAnimatedSprite(const std::string& filepath, const ImageFormat& format) {
	mnoptrAnimatedSprite = new AnimatedSprite(mRender, filepath, format);
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
	else if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetPosition(x, y);
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

void GameEntity::AddAnimation(const std::string& animationName, int yStartPositionInSpritesheet, int numberFrames) {
	mAnimations.insert(std::make_pair(animationName, std::make_pair(yStartPositionInSpritesheet, numberFrames)));
}

void GameEntity::ChangeAnimation(const std::string& animationName) {
	mFrame = 0;
	mCurrentAnimationName = animationName;
	mAnimationDelayCount = 0;
	if (mnoptrAnimatedSprite) {
		mnoptrAnimatedSprite->SetCountSpeed(0);
	}
}