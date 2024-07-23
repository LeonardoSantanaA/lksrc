#include <memory>
#include "Entities/Enemies/Zombie.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"

Zombie::Zombie(const std::string& name) : Enemy::Enemy(name)
{
	AddAnimatedSprite("assets/images/enemies/zombie.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 8);
	AddAnimation("attacking", 32, 7);
	AddAnimation("run", 64, 8);
	AddAnimation("attack_0", 32, 7);
	mMaxVelocity = 2.0f; 
	mStepVelocity = 0.2f;
	mMaxDelayJump = 20; 
	SetDimensions(32, 32);
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(22, 25);
	SetOffsetPositionCollision(0, 5, 6);
	SetDebugMode(true);
}

void Zombie::Update() {
	Enemy::Update();
}

