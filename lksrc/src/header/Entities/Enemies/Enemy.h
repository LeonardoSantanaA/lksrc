#pragma once

#include "Managers/GameEntity.h"
#include "Entities/Enemies/EnemyHit.h"

enum EnemyCurrentAnimation {
	IDLE = 0,
	RUNNING,
	ATTACKING,
	JUMPING,
	DAMAGE,
	DEAD
};

class Enemy : public GameEntity{
public:
	Enemy(const std::string& name);
	virtual ~Enemy() {};
	virtual void Update() override;
	inline float GetLife() const { return mLife; }
	void TakeDamage(float damage, GameEntity& hitOwner);

protected:
	float mLife;

	float vSpd;
	float grvt;

	int mDirection, mCurrentDirection;

	float mVelocity;
	float mMaxVelocity;
	float mStepVelocity;

	int mFrameStartToAttack;
	int mFrameEndToAttack;
	bool mCanAttack;
	bool mIsAttacking;
	bool mCanHit;
	int mDelayAttack;
	int mMaxDelayAttack;

	bool mCanJump;
	int mCurrentDelayJump;
	int mMaxDelayJump;

	int distanceToPlayer;
	int currentAnimationAttack;
	int maxAnimationAttack;

	float mHitKnockback;
	float mKnockbackDefending;

	void Gravity();
	bool HorizontalMovement();
	virtual void AnimationState();
	virtual void Move();
	virtual void Jump();
	virtual void Attack();
	void ResetVelocity();
	inline void SetKnockBack(float knockback) { mKnockback = knockback; }
	inline void SetLife(float life) { mLife = life; }

	bool isTakingDamage;

	EnemyCurrentAnimation currentAnimation;
	float mIdleAnimationSpeed, mRunAnimationSpeed, mAttackAnimationSpeed, mJumpAnimationSpeed, mDamageAnimationSpeed, mDeadAnimationSpeed;

	std::string mDir;
	EnemyHit mHit;

	float mKnockback;
};
