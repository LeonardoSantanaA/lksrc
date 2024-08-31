#pragma once

#include <SDL.h>
#include "Managers/GameEntity.h"
#include "Entities/PlayerHit.h"

enum PlayerStates {
	PLAYER_IDLE = 0,
	PLAYER_CHANGE_POSITION,
	PLAYER_RUNNING,
	PLAYER_ATTACKING,
	PLAYER_DEFENDING,
	PLAYER_ROLLING,
	PLAYER_JUMPING,
	PLAYER_DAMAGE,
	PLAYER_DEAD
};

class Player : public GameEntity {
public:
	Player(const std::string& name);
	
	virtual void Update() override;

	virtual void Render() override;
	void ChangeDirection(int dir);

	void TakeDamage(float damage, float knockback);

	inline bool IsDefending() const { return isDefending; }

	inline float GetLife() const { return mLife; }
	inline float GetStamina() const { return mStamina; }
	inline void TakeStamina(float value) { mStamina -= value; }

private:
	float mLife;
	float mMaxLife;
	float mStepLife;
	float mStamina;
	float mMaxStamina;
	float mStepStamina;

	bool isMoving;
	float moveDelay;
	float maxMoveDelay;

	bool canJump;
	bool isJumping;
	int delayJump;

	int mDirection;
	bool inChangeDirection;
	bool canChangeDirection;
	int mDelayCanChangeDirection;

	float mVelocity;
	float mMaxVelocity;
	float mStepVelocity;

	PlayerStates mCurrentState;
	PlayerHit mHit;
	
	bool isRolling;
	bool canRoll;
	int mDelayCanRoll;

	float vSpd;
	const float grvt;

	void AnimationState();

	bool isAttacking;
	int currentIndexAttack;
	std::string nameCurrentAnimationAttack;
	float currentDelayAttack;
	const float maxDelayAttack;
	float currentDelayComboAttack;
	const float maxDelayComboAttack;
	bool canHit;

	bool canPrepareToDefend;
	bool preparingToDefend;
	bool isDefending;

	bool isDead;
	bool takingDamage;
	int mDelayTakingDamage;

	void InputHandle();
	void Move(int dir);
	void Attack();
	void Defense();
	void Roll();
	void Gravity();
	void Jump();
	bool HorizontalMovement();
	void ResetVelocity();

	//sounds
	int sndAttack;
	int sndAttackDeffense;
	int sndDamage;
	int sndRoll;

	//return if player can do another movement
	bool CanAct() const;

};