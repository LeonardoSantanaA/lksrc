#pragma once

#include <SDL.h>
#include "Managers/GameEntity.h"


class Player : public GameEntity {
public:
	Player(const std::string& name);
	
	virtual void Update() override;
	
	//virtual void Render() override;
	void ChangeDirection(const char* dir);

private:
	bool onGround;
	bool isMoving;
	float moveDelay;
	float maxMoveDelay;

	bool canJump;
	bool isJumping;
	int delayJump;
	bool inChangeDirection;
	bool isAttacking;
	bool canChangeDirection;
	float delayCanChangeDirection;

	const char* mDirection;
	float mVelocity;
	float mMaxVelocity;
	float mStepVelocity;
	float mFactorVelocity;
	
	float vSpd;
	float grvt;

	void AnimationState();

	int currentIndexAttack;
	std::string nameCurrentAnimationAttack;
	float currentDelayAttack;
	float maxDelayAttack;
	float currentDelayComboAttack;
	float maxDelayComboAttack;

	void Attack();
	void Gravity();
	void Jump();
	bool HorizontalMovement();
	void ResetVelocity();
};