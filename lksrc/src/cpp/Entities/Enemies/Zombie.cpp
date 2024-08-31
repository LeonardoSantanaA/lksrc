#include <memory>
#include "Entities/Enemies/Zombie.h"
#include "Collision/Collisor.h"
#include "Managers/EntityManager.h"
#include "Core/Sound.h"

Zombie::Zombie(const std::string& name) : Enemy::Enemy(name)
{
	AddAnimatedSprite("assets/images/enemies/zombie.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 8);
	AddAnimation("run", 64, 8);
	AddAnimation("jump", 64, 8);
	AddAnimation("attack_0", 32, 7);
	AddAnimation("damage", 160, 4);
	AddAnimation("death", 128, 8);
	mMaxVelocity = 2.0f; 
	mStepVelocity = 0.2f;
	mMaxDelayJump = 20; 
	distanceToPlayer = 40;
	SetDimensions(32, 32);
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(22, 8);
	SetOffsetPositionCollision(0, 5, 6);
	//SetDebugMode(true);
	mFrameStartToAttack = 4;
	mFrameEndToAttack = 5;
	mHit.SetDamage(25.0f);
	SetLife(10.0f);

	sndDamage = Sound::GetInstance()->LoadSound("assets/snd/soundEffects/zombieDamage.wav");
}
