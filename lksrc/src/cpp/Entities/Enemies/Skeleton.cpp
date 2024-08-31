#include <memory>
#include "Entities/Enemies/Skeleton.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"
#include "Managers/EnemyManager.h"
#include "Entities/Player.h"
#include "Core/Sound.h"

Skeleton::Skeleton(const std::string& name) : Enemy::Enemy(name)
{
	AddAnimatedSprite("assets/images/enemies/skeleton.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(64, 48);
	AddAnimation("idle", 144, 4);
	AddAnimation("run", 96, 12);
	AddAnimation("jump", 96, 12);
	AddAnimation("attack_0", 0, 13);
	AddAnimation("damage", 192, 3);
	AddAnimation("death", 48, 13);
	mMaxVelocity = 1.8f;
	mStepVelocity = 0.2f;
	mMaxDelayJump = 20;
	distanceToPlayer = 40;
	SetDimensions(64, 48, 1.8f);
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(23, 15, 1.8f);
	SetOffsetPositionCollision(0, 21, 17, 1.8f);
	//SetDebugMode(true);
	mHit.SetDamage(30.0f);
	mHit.SetDimensions(64, 32, 1.0f);
	mFrameStartToAttack = 5;
	mFrameEndToAttack = 7;
	SetLife(20.0f);
	mCanHit2 = true;

	sndDamage = Sound::GetInstance()->LoadSound("assets/snd/soundEffects/skeletonDamage.wav");
}

void Skeleton::AnimationState() {
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

		Vec2D currentPos = mCurrentDirection > 0 ? Vec2D(GetVec2D(0).x + 20, GetVec2D(0).y + 5) : Vec2D(GetVec2D(0).x - 40, GetVec2D(0).y + 5);
		std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");
		mIsAttacking = true;

		if ((GetCurrentAnimationFrame() >= mFrameStartToAttack && GetCurrentAnimationFrame() <= mFrameEndToAttack && mCanHit)) {
			mHit.SetPosition(currentPos);
			
			if (mHit.IsHitting(*player)) {
				mCanHit = false;
				player->TakeDamage(mHit.GetDamage(), mHitKnockback * mDirection);
			}
		}

		if ((GetCurrentAnimationFrame() >= 9 && GetCurrentAnimationFrame() <= 10) && mCanHit2) {
			mHit.SetPosition(currentPos);
			if (mHit.IsHitting(*player)) {
				mCanHit2 = false;
				player->TakeDamage(mHit.GetDamage() + 3.0f, mHitKnockback * mDirection);
			}
		}

		if (IsLastFrame()) {
			mDelayAttack = 0;
			mIsAttacking = false;
			mCanAttack = false;
			mCanHit = true; 
			mCanHit2 = true;
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

void Skeleton::Attack() {
	if (mCanAttack && !isTakingDamage) {
		currentAnimationAttack++;
		if (currentAnimationAttack >= maxAnimationAttack) {
			currentAnimationAttack = 0;
		}
		currentAnimation = ATTACKING;

	}
}