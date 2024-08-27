#include <memory>
#include "Entities/Enemies/Wolf.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"
#include "Entities/Player.h"

Wolf::Wolf(const std::string& name) : Enemy::Enemy(name)
{
	AddAnimatedSprite("assets/images/enemies/wolf.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(48, 32);
	AddAnimation("idle", 0, 4);
	AddAnimation("run", 32, 6);
	AddAnimation("jump", 32, 6);
	AddAnimation("attack_0", 64, 7);
	AddAnimation("damage", 128, 4);
	AddAnimation("death", 96, 8);
	mMaxVelocity = 2.5f;
	mStepVelocity = 0.25f;
	mMaxDelayJump = 20;
	distanceToPlayer = 100;
	mMaxDelayAttack = 50;
	SetDimensions(48, 32);
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(40, 5);
	SetOffsetPositionCollision(0, 5, 10);
	//SetDebugMode(true);
	mHit.SetDamage(20.0f);
	mFrameStartToAttack = 2;
	mFrameEndToAttack = 4;
	FlipHorizontal();
}

void Wolf::Attack() {
	if (mCanAttack && !isTakingDamage) {
		currentAnimation = ATTACKING;
		std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");
		mIsAttacking = true;
		mVelocity = 6.0f * mDirection;
	}
}