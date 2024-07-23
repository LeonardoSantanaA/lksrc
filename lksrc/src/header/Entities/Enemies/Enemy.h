#pragma once

#include "Managers/GameEntity.h"

enum EnemyCurrentAnimation {
	IDLE = 0,
	RUNNING,
	ATTACKING,
	JUMPING
};

class Enemy : public GameEntity {
public:
	Enemy(const std::string& name);

	virtual void Update() override;

protected:
	float vSpd;
	float grvt;
	float mVelocity;
	float mMaxVelocity;
	float mStepVelocity;
	bool mIsAttacking;
	bool canJump;
	bool mCanAttack;
	int mCurrentDelayAttack;
	int mMaxDelayAttack;
	int mCurrentDelayJump;
	int mMaxDelayJump;
	int distanceToPlayer;
	int currentAnimationAttack;
	int maxAnimationAttack;

	void Gravity();
	bool HorizontalMovement();
	void AnimationState();
	void Move();
	void Jump();
	void Attack();

	EnemyCurrentAnimation currentAnimation;
	std::string mDir;
};
