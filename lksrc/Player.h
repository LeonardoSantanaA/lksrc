#pragma once

#include "GameEntity.h"
#include <SDL.h>

class Player : public GameEntity {
public:
	Player(const std::string& name);

	virtual void Update() override;
	//virtual void Render() override;
	void ChangeDirection(const char* dir);
	SDL_Rect rectTest;

private:
	bool isMoving;
	const char* mDirection;
	float mVelocity;

	float vSpd;
	float grvt;

	void Gravity();
	bool IsHorizontalColliding(const char* dir);
};