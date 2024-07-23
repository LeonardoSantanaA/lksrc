#include <memory>
#include "Entities/Enemies/Enemy.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"

Enemy::Enemy(const std::string& name) : GameEntity::GameEntity(name),
vSpd(0.0f), grvt(0.8f), mVelocity(0.0f), mMaxVelocity(2.0f), mStepVelocity(0.2f), canJump(false), mMaxDelayJump(20), mCurrentDelayJump(0), distanceToPlayer(50), mIsAttacking(false), currentAnimationAttack(0), maxAnimationAttack(1), mCanAttack(false)
{
	currentAnimation = IDLE;
}

void Enemy::Update() {
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();
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
		canJump = true;
		vSpd = 0;
	}
	else {
		canJump = false;
	}

	if (mCurrentDelayJump <= mMaxDelayJump) {
		mCurrentDelayJump++;
		canJump = false;
	}
	MovePosition(0.0f, vSpd);

}

void Enemy::Move() {
	std::shared_ptr<GameEntity> player = EntityManager::GetInstance()->GetEntityRef("PLAYER");
	if (player && player->GetVec2D(0).Distance(GetVec2D(0)) > distanceToPlayer) {
		//left
		if (player->GetVec2D(0).x > GetVec2D(0).x) {
			if (mVelocity < mMaxVelocity) {
				mVelocity += mStepVelocity;
				currentAnimation = RUNNING;
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
			}
			else {
				mVelocity = -mMaxVelocity;
			}
		}
	}
	else {
		Attack();
	}

}

bool Enemy::HorizontalMovement() {

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
	if (canJump && !mIsAttacking) {
		currentAnimation = JUMPING;
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
	if (mCanAttack) {
		currentAnimationAttack++;
		if (currentAnimationAttack >= maxAnimationAttack) {
			currentAnimationAttack = 0;
		}
		mIsAttacking = true;
	}
}

void Enemy::AnimationState() {
	switch (currentAnimation) {
	case IDLE:
		ChangeAnimation("idle");
		SetAnimationLoop(true);
		SetAnimationSpeed(10.0f);
		break;

	case RUNNING:
		ChangeAnimation("run");
		SetAnimationLoop(true);
		SetAnimationSpeed(10.0f);
		break;

	case JUMPING:

		break;

	case ATTACKING:
		std::string animation = "attack_" + currentAnimationAttack;
		ChangeAnimation(animation);
		SetAnimationLoop(false);
		SetAnimationSpeed(5.0f);
		if (IsLastFrame()) {
			mIsAttacking = false;
		}
		break;
	}
}