#pragma once

#include "GameEntity.h"
#include <SDL.h>

class Player : public GameEntity {
public:
	Player(const std::string& name);
	
	virtual void Update() override;
	
	//virtual void Render() override;
	void ChangeDirection(const char* dir);

private:
	bool onGround;
	bool isMoving;

	bool canJump;
	bool isJumping;
	int delayJump;

	const char* mDirection;
	float mVelocity;

	float vSpd;
	float grvt;

	void AnimationState();

	void Gravity();
	void Jump();
	bool IsHorizontalColliding(const char* dir);
};