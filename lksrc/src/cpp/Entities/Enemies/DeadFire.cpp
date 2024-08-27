#include "Entities/Enemies/DeadFire.h"
#include "Entities/Player.h"
#include "Managers/EntityManager.h"

DeadFire::DeadFire(const std::string& name): GameEntity::GameEntity(name),
	mDir(1), mVelocity(8.0f) {
	AddAnimatedSprite("assets/images/enemies/fire.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(16, 28);
	SetDimensions(16, 28, 3.0f);
	AddAnimation("attack", 0, 3);
	SetAnimationLoop(false);
	SetAnimationSpeed(5.0f);
	ChangeAnimation("attack");
	AddCollider2D();
	GetCollider2D(0)->SetDimensions(24, 30);
	mHit.SetDamage(5.0f);
	mHit.SetDimensions(16, 38, 3.0f);
}

void DeadFire::Update() {
	GameEntity::Update();
	GameEntity::UpdateSpriteSheet();

	MovePosition(mVelocity * static_cast<float>(mDir), 0.0f);
	mHit.SetPosition(GetVec2D(0));

	std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");

	if (mHit.IsHitting(*player)) {
		player->TakeDamage(mHit.GetDamage(), 0.0f);
		EntityManager::GetInstance()->RemoveEntity(this->GetName());
	}

	if (IsLastFrame()) {
		EntityManager::GetInstance()->RemoveEntity(this->GetName());
	}

}