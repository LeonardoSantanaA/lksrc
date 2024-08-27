#include <memory>
#include "Entities/Enemies/Dead.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"
#include "Managers/EnemyManager.h"
#include "Entities/Player.h"
#include "Entities/Enemies/DeadFire.h"

Dead::Dead(const std::string& name) : Enemy::Enemy(name), mCanCreateFire(true)
{
	AddAnimatedSprite("assets/images/enemies/dead.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(80, 80);
	AddAnimation("idle", 0, 8);
	AddAnimation("run", 0, 8);
	AddAnimation("jump", 0, 8);
	AddAnimation("attack_0", 80, 8);
	AddAnimation("damage", 160, 2);
	AddAnimation("death", 240, 12);
	mMaxVelocity = 2.0f;
	mStepVelocity = 0.2f;
	mMaxDelayJump = 20;
	distanceToPlayer = 100;
	mMaxDelayAttack = 35;
	SetDimensions(80, 80);
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(24, 30);
	SetOffsetPositionCollision(0, 27, 30);
	//SetDebugMode(true);
	mFrameStartToAttack = 4;
	mFrameEndToAttack = 5;
	mHit.SetDamage(25.0f);
	mHit.SetDimensions(46, 46, 1.0f);
	SetLife(30.0f);
}

void Dead::AnimationState() {
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
		Vec2D currentPos = mCurrentDirection > 0 ? Vec2D(GetVec2D(0).x + 40, GetVec2D(0).y + 5) : Vec2D(GetVec2D(0).x - 40, GetVec2D(0).y + 5);
		std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");
		if (GetCurrentAnimationFrame() == mFrameStartToAttack && mCanCreateFire) {
			std::cout << "CRIAR!" << std::endl;
			mCanCreateFire = false;
			if (EntityManager::GetInstance()->CreateEntityType("DEADFIRE")) {
				std::shared_ptr<DeadFire> fire = EntityManager::GetInstance()->GetEntityRef<DeadFire>("DEADFIRE");
				if (fire) {
					fire->SetPosition(currentPos.x, currentPos.y);
					fire->SetDir(mDirection);
					if (mDirection < 0)
						fire->FlipHorizontal();
				}
			}
			
		}
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
			mCanCreateFire = true;
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