#pragma once

#include <unordered_map>
#include <vector>
#include "Graphics/TexturedRectangle.h"
#include "Collision/Collider2D.h"
#include "Graphics/AnimatedSprite.h"
#include "Camera/Point.h"
#include "Graphics/RenderEntityLayer.h"

class GameEntity {
public:
	GameEntity();
	GameEntity(const std::string& name);

	virtual ~GameEntity();

	//you can configure a init() function to call after file load .lkobj, the ParseEntities() will try to call this function.
	virtual void Init() {};

	virtual void Update();
	void UpdateSpriteSheet();
	virtual void Render();

	inline std::string GetName() { return mName; }
	void AddTexturedRectangleComponent(const std::string& filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddTexturedRectangleComponent(const std::string& filepath, int red, int green, int blue, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddAnimatedSprite(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);

	void AddCollider2D();

	//return true if is coliding with another entity
	SDL_bool IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex);

	int GetCurrentAnimationFrame() const;

	//return true if the current frame playing is the last
	bool IsLastFrame();

	//set offset position for collider rectangle
	void SetOffsetPositionCollision(int indexCollision, int xoffsetCollision, int yoffsetCollision, float scale = SCALE);

	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
	void MovePosition(float x, float y);
	void SetDimensions(int w, int h, float scale = SCALE);
	void AddAnimation(const std::string& animationName, int yStartPositionInSpritesheet, int numberFrames);
	std::string GetCurrentAnimation() const;
	void ChangeAnimation(const std::string& animationName);
	void AddPoint();
	
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
	inline Point* GetPoint() { return mPoint.get(); }
	inline RenderEntityLayer GetRenderLayer() const{ return mRenderLayer; }
	inline void SetRenderLayer(const RenderEntityLayer& renderLayer) { mRenderLayer = renderLayer; }
	inline Vec2D GetVec2D(int index) { return Vec2D(GetCollider2D(index)->GetColliderBoundingBox()->x, GetCollider2D(index)->GetColliderBoundingBox()->y); }

protected:
	std::string mName;
	std::unique_ptr<TexturedRectangle> mnoptrSprite;
	std::unique_ptr<AnimatedSprite> mnoptrAnimatedSprite;
	std::vector<std::unique_ptr<Collider2D>> mnoptrColliders;
	std::unique_ptr<Point> mPoint;

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

	RenderEntityLayer mRenderLayer;
};