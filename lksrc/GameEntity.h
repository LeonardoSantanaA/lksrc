#pragma once

#include "TexturedRectangle.h"
#include <vector>
#include "Collider2D.h"
#include "Layer.h"
#include "AnimatedSprite.h"
#include <unordered_map>

class GameEntity {
public:
	GameEntity();
	GameEntity(const std::string& name, SDL_Renderer* render);

	~GameEntity();

	void Update();
	void UpdateSpriteSheet();
	void Render();
	void Render(const std::string& animationName, bool loop, float speed);

	void AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddAnimatedSprite(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);

	void AddCollider2D();

	SDL_bool IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex);

	void SetPosition(int x, int y, int indexCollision = 0, int xoffsetCollision = 0, int yoffsetCollision = 0);
	void SetDimensions(int w, int h, float scale = SCALE);
	void AddAnimation(const std::string& animationName, int yStartPositionInSpritesheet, int numberFrames);
	void ChangeAnimation(const std::string& animationName);
	
	inline TexturedRectangle& GetTexturedRectangle() const{
		if (mnoptrSprite) {
			return *mnoptrSprite;
		}
		std::cout << "trying access a nullptr. gameentity::gettexturedrectangle()." << std::endl;
	}

	inline Collider2D* GetCollider2D(size_t index) {
		if (mnoptrColliders[index]) {
			return mnoptrColliders[index];
		}
		std::cout << "trying access a nullptr. gameentity::getcollider2D(), index: " << index << std::endl;
		return nullptr;
	}

	inline void SetAnimatedSpriteDimensions(int w, int h, float scale = 1.0f) {
		if (mnoptrAnimatedSprite) {
			mnoptrAnimatedSprite->SetDimensions(w, h, scale);
		}
	}

	inline int GetX() { if (mnoptrSprite) { return mnoptrSprite->GetX(); } std::cout << "getx() from nullptr sprite." << std::endl;  return -1; }
	inline int GetY() { if (mnoptrSprite) { return mnoptrSprite->GetY(); } std::cout << "gety() from nullptr sprite." << std::endl;  return -1; }
	inline int GetWidth() { if (mnoptrSprite) { return mnoptrSprite->GetWidth(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }
	inline int GetHeight() { if (mnoptrSprite) { return mnoptrSprite->GetHeight(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }
	inline void SetDebugMode(bool debugMode) { mDebugMode = debugMode; }
	inline Layer GetLayer() const { return mLayer; }
	inline void SetLayer(Layer layer) { mLayer = layer; }
	inline void SetAngleRotate(float angle) { mnoptrSprite->SetAngle(angle); mAngle = angle; }
	inline void SetCenterPointRotate(const SDL_Point& point) { mnoptrSprite->SetCenterPointRotate(point); mCenterPoint = point; }
	inline void FlipHorizontal() { mnoptrSprite->FlipImageHorizontal(); }
	inline void FlipVertical() { mnoptrSprite->FlipImageVertical(); }
	inline void SetAnimatedSpriteDimensionsInSpriteSheet(int w, int h) { mAnimatedSpriteWidth = w; mAnimatedSpriteHeight = h; }
	inline void SetAnimationLoop(bool loop) { mLoop = loop; }
	inline void SetAnimationSpeed(float speed) { mAnimationSpeed = speed; }

private:
	std::string mName;
	Layer mLayer;
	TexturedRectangle* mnoptrSprite;
	AnimatedSprite* mnoptrAnimatedSprite;
	std::vector<Collider2D*> mnoptrColliders;
	SDL_Renderer* mRender;

	std::string mCurrentAnimationName;
	int mAnimationDelayCount;
	bool mLoop;
	int mFrame;
	float mAnimationSpeed;
	int mAnimatedSpriteWidth;
	int mAnimatedSpriteHeight;
	std::pair<int, int> pairAnimation;
	std::unordered_map<std::string, std::pair<int, int>> mAnimations;

	bool mDebugMode;
	float mAngle;
	SDL_Point mCenterPoint;
	
};