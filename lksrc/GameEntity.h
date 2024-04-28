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

	virtual void Update();
	void UpdateSpriteSheet();
	virtual void Render();

	void AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddAnimatedSprite(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);

	void AddCollider2D();

	SDL_bool IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex);
	void SetOffsetPositionCollision(int indexColission, int xoffsetCollision, int yoffsetColision);

	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
	void SetDimensions(int w, int h, float scale = SCALE);
	void AddAnimation(const std::string& animationName, int yStartPositionInSpritesheet, int numberFrames);
	std::string GetCurrentAnimation() const;
	void ChangeAnimation(const std::string& animationName);
	
	TexturedRectangle& GetTexturedRectangle() const;
	Collider2D* GetCollider2D(size_t index);
		
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	void SetAngleRotate(float angle);
	void SetCenterPointRotate(const SDL_Point& point);
	void FlipHorizontal();
	void FlipVertical();

	inline void SetAnimatedSpriteDimensionsInSpriteSheet(int w, int h) { mAnimatedSpriteWidth = w; mAnimatedSpriteHeight = h; }
	inline void SetAnimationLoop(bool loop) { mLoop = loop; }
	inline void SetAnimationSpeed(float speed) { mAnimationSpeed = speed; }
	inline void SetDebugMode(bool debugMode) { mDebugMode = debugMode; }
	inline Layer GetLayer() const { return mLayer; }
	inline void SetLayer(Layer layer) { mLayer = layer; }

protected:
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