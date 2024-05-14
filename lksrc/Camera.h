#pragma once

#include <SDL.h>
#include "Vec2D.h"
#include "Point.h"

class Camera {
public:
	static Camera* GetInstance();
	void Clean();

	inline const SDL_Rect GetViewBox() const { return mViewBox; }
	inline const Vec2D GetPosition() const { return mPosition; }

	//Set the target to camera follows.
	//use the GetPoint() for GameEntity.
	inline void SetTarget(Point* target) { mTarget = target; };

	void Update();

private:
	Camera();
	static Camera* mInstance;
	Point* mTarget;
	Vec2D mPosition;
	SDL_Rect mViewBox;

};