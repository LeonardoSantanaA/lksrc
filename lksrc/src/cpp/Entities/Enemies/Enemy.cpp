#include <memory>
#include <iostream>
#include "Entities/Enemies/Enemy.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"
#include "Managers/EnemyManager.h"
#include "Entities/Player.h"

Enemy::Enemy(const std::string& name) : GameEntity::GameEntity(name),
vSpd(0.0f), grvt(0.8f), mVelocity(0.0f), mMaxVelocity(2.0f), mStepVelocity(0.2f), mCanJump(false), mMaxDelayJump(20), mCurrentDelayJump(0), distanceToPlayer(50), mIsAttacking(false), currentAnimationAttack(0), maxAnimationAttack(1), mCanAttack(false), mDelayAttack(0), mMaxDelayAttack(28.0f), mDirection(1), mCurrentDirection(1), mHit(), isTakingDamage(false), mKnockback(0.5f), mLife(5.0f), mHitKnockback(3.0f), mKnockbackDefending(1.5f), mFrameStartToAttack(4), mFrameEndToAttack(6), mIdleAnimationSpeed(10.0f), mRunAnimationSpeed(10.0f), mAttackAnimationSpeed(5.0f), mDamageAnimationSpeed(3.0f), mDeadAnimationSpeed(7.0f), mJumpAnimationSpeed(5.0f)
{	
	currentAnimation = IDLE;
	SetKnockBack(5.0f);
	mHit.SetDamage(3.0f);
	mHit.SetDimensions(32, 32, 1.0f);
	EnemyManager::GetInstance()->AddEnemy(this);
	mCanHit = true;

}

void Enemy::Update() {
	GameEntity::UpdateSpriteSheet();
	AnimationState();
	Gravity();
	HorizontalMovement();
	Move();
}

void Enemy::Gravity() {
	vSpd = vSpd + grvt;

	if (!Collisor::GetInstance()->PlaceFree(
		GetCollider2D(0)->GetColliderBoundingBox()->x,
		static_cast<int>(GetCollider2D(0)->GetColliderBoundingBox()->y + vSpd),
		GetCollider2D(0)->GetColliderBoundingBox()->w,
		GetCollider2D(0)->GetColliderBoundingBox()->h)) {
		while (Collisor::GetInstance()->PlaceFree(
			GetCollider2D(0)->GetColliderBoundingBox()->x,
			GetCollider2D(0)->GetColliderBoundingBox()->y + Sign(vSpd),
			GetCollider2D(0)->GetColliderBoundingBox()->w,
			GetCollider2D(0)->GetColliderBoundingBox()->h)) {
			MovePosition(0, Sign(vSpd));
		}
		mCanJump = true;
		vSpd = 0;

	}
	else {
		mCanJump = false;
	}

	if (mCurrentDelayJump <= mMaxDelayJump) {
		mCurrentDelayJump++;
		mCanJump = false;
	}
	MovePosition(0.0f, vSpd);

}

void Enemy::Move() {
	if (!mCanAttack && !isTakingDamage) {
		if (mDelayAttack < mMaxDelayAttack) {
			mDelayAttack++;
		}
		else {
			mCanAttack = true;
		}
	}

	std::shared_ptr<GameEntity> player = EntityManager::GetInstance()->GetEntityRef<GameEntity>("PLAYER");
	if (player && player->GetVec2D(1).Distance(GetVec2D(0)) > distanceToPlayer && !mIsAttacking && !isTakingDamage) {
		//left
		if (player->GetVec2D(0).x > GetVec2D(0).x) {
			if (mVelocity < mMaxVelocity) {
				mVelocity += mStepVelocity;
				currentAnimation = RUNNING;
				mDirection = 1;
			}
			else {
				mVelocity = mMaxVelocity;
			}
		}

		//right
		if (player->GetVec2D(0).x < GetVec2D(0).x) {
			if (mVelocity > -mMaxVelocity) {
				mVelocity -= mStepVelocity;
				currentAnimation = RUNNING;
				mDirection = -1;
			}
			else {
				mVelocity = -mMaxVelocity;
			}
		}

	}else {
		ResetVelocity();
		Attack();
	}

}

bool Enemy::HorizontalMovement() {

	if (mDirection != mCurrentDirection) {
		FlipHorizontal();
		mCurrentDirection = mDirection;
	}

	if (!Collisor::GetInstance()->PlaceFree(
		static_cast<int>(GetCollider2D(0)->GetColliderBoundingBox()->x + mVelocity),
		GetCollider2D(0)->GetColliderBoundingBox()->y,
		GetCollider2D(0)->GetColliderBoundingBox()->w,
		GetCollider2D(0)->GetColliderBoundingBox()->h)) {
		while (Collisor::GetInstance()->PlaceFree(
			GetCollider2D(0)->GetColliderBoundingBox()->x + Sign(mVelocity),
			GetCollider2D(0)->GetColliderBoundingBox()->y,
			GetCollider2D(0)->GetColliderBoundingBox()->w,
			GetCollider2D(0)->GetColliderBoundingBox()->h)) {
			MovePosition(Sign(mVelocity), 0);
		}
		Jump();

		return false;
	}

	MovePosition(mVelocity, 0.0f);

	return true;
}

void Enemy::Jump() {
	if (mCanJump && !mIsAttacking && !isTakingDamage) {
		//currentAnimation = JUMPING;
		mCurrentDelayJump = 0;
		vSpd = -12;
		if (!Collisor::GetInstance()->PlaceFree(
			GetCollider2D(0)->GetColliderBoundingBox()->x,
			GetCollider2D(0)->GetColliderBoundingBox()->y - 1,
			GetCollider2D(0)->GetColliderBoundingBox()->w,
			GetCollider2D(0)->GetColliderBoundingBox()->h)) {
			vSpd = 1;
		}
	}
}

void Enemy::Attack() {
	if (mCanAttack && !isTakingDamage) {
		currentAnimationAttack++;
		if (currentAnimationAttack >= maxAnimationAttack) {
			currentAnimationAttack = 0;
		}
		currentAnimation = ATTACKING;

		mIsAttacking = true;

	}
}

void Enemy::AnimationState() {
	switch (currentAnimation) {
	case IDLE:
	{
		ChangeAnimation("idle");
		SetAnimationLoop(true);
		SetAnimationSpeed(mIdleAnimationSpeed);

		break;
	}

	case RUNNING:
	{
		ChangeAnimation("run");
		SetAnimationLoop(true);
		SetAnimationSpeed(mRunAnimationSpeed);

		break;
	}

	case JUMPING:
		ChangeAnimation("jump");
		SetAnimationLoop(false);
		SetAnimationSpeed(mJumpAnimationSpeed);
		break;

	case ATTACKING:
	{
		std::string animation = "attack_" + std::to_string(currentAnimationAttack);
		ChangeAnimation(animation);
		SetAnimationLoop(false);
		SetAnimationSpeed(mAttackAnimationSpeed);
		Vec2D currentPos = mCurrentDirection > 0 ? Vec2D(GetVec2D(0).x + 20, GetVec2D(0).y + 5) : Vec2D(GetVec2D(0).x - 10, GetVec2D(0).y + 5);
		std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");
		if (GetCurrentAnimationFrame() >= mFrameStartToAttack && GetCurrentAnimationFrame() <= mFrameEndToAttack && mCanHit) {
			mHit.SetPosition(currentPos);
			if (mHit.IsHitting(*player)) {
				mCanHit = false;
				player->TakeDamage(mHit.GetDamage(), mHitKnockback * mDirection);
			}
		}

		if (IsLastFrame()) {
			mDelayAttack = 0;
			mIsAttacking = false;
			mCanAttack = false;
			mCanHit = true;
			currentAnimation = IDLE;
		}

		break;
	}

	case DAMAGE:
	{
		ChangeAnimation("damage");
		SetAnimationLoop(false);
		SetAnimationSpeed(mDamageAnimationSpeed);

		if (IsLastFrame()) {
	
			if (mLife <= 0.0f) {
				currentAnimation = DEAD;
			}
			else {
				isTakingDamage = false;
			}
			
		}
	}

	break;

	case DEAD:
	{
		ChangeAnimation("death");
		SetAnimationLoop(true);
		SetAnimationSpeed(mDeadAnimationSpeed);
		if (IsLastFrame()) {
			EnemyManager::GetInstance()->RemoveEnemy(*this);
			EntityManager::GetInstance()->RemoveEntity(GetName());
		}
		break;
	}
	}
	
}

void Enemy::ResetVelocity() {
	if (mVelocity > 0) {
		mVelocity -= mStepVelocity;
		if (mVelocity < 0) {
			mVelocity = 0;
		}
	}

	if (mVelocity < 0) {
		mVelocity += mStepVelocity;
		if (mVelocity > 0) {
			mVelocity = 0;
		}
	}
}

void Enemy::TakeDamage(float damage, GameEntity& hitOwner) {
		isTakingDamage = true;
		currentAnimation = DAMAGE;
		mLife -= damage;
		if (hitOwner.GetVec2D(0).x > GetVec2D(0).x) {
			mVelocity = -mKnockback;
		}
		else {
			mVelocity = mKnockback;
		}
}