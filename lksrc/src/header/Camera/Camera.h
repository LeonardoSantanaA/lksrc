#pragma once

#include <SDL.h>
#include "Physics/Vec2D.h"
#include "Camera/Point.h"

class Camera {
public:
	static Camera* GetInstance();
	void Clean();

	void Reset();
	inline int GetSceneWidth() const { return mSceneWidth; }
	inline int GetSceneHeight() const { return mSceneHeight; }
	inline const SDL_Rect GetViewBox() const { return mViewBox; }
	inline const Vec2D GetPosition() const { return mPosition; }

	//Set the target to camera follows.
	//use the GetPoint() for GameEntity to set the target.
	inline void SetTarget(Point* target) { mTarget = target; };

	//set the limit of the camera
	inline void SetSceneLimit(int w, int h) { mSceneWidth = w; mSceneHeight = h; }

	inline float GetZoom() const { return mZoom; }

	//set a zoom to aproximate the camera from elements
	void SetZoom(float zoom);

	void Update();

	//reload the camera resolution
	void Reload();

private:
	Camera();
	static Camera* mInstance;
	Point* mTarget;
	Vec2D mPosition;
	SDL_Rect mViewBox;
	int mCameraWidth, mCameraHeight;
	int mSceneWidth, mSceneHeight;
	float mZoom;

};