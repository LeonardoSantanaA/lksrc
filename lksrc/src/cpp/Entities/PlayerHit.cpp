#include "Entities/PlayerHit.h"
#include "Managers/EntityManager.h"
#include "Managers/Utils.h"

PlayerHit::PlayerHit(GameEntity* entityOwn) :mnoptrCollider(nullptr), mDamage(0), mPos(Vec2D::Zero), mOwn(entityOwn) {
	mnoptrCollider = std::make_unique<Collider2D>();
}

void PlayerHit::SetPosition(const Vec2D& pos) {
	mPos = pos;
	if (mnoptrCollider) {
		mnoptrCollider->SetPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}

void PlayerHit::SetDimensions(int w, int h, float scale) {
	if (mnoptrCollider) {
		mnoptrCollider->SetDimensions(w, h, scale);
	}
}

Enemy* PlayerHit::IsHitting() {
	if (mnoptrCollider) {
		auto enemies = EntityManager::GetInstance()->GetEntities<Enemy>();
		for (const auto& pair : *enemies) {
			const auto& enemy = pair.second;
			if (mnoptrCollider->IsColliding(*enemy->GetCollider2D(0))) {
				return EntityManager::GetInstance()->GetEntityRef<Enemy>(enemy->GetName()).get();
			}
		}

	}
	return nullptr;
}

void PlayerHit::SetDamage(float damage) {
	mDamage = damage;
}

void PlayerHit::Render() {
	//show what draw
	if (mnoptrCollider) {
		mnoptrCollider->Render();
	}

	SDL_RenderPresent(Engine::GetInstance()->GetRender());
}