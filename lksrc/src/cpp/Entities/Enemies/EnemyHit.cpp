#include "Entities/Enemies/EnemyHit.h"
#include "Managers/EntityManager.h"
#include "Managers/Utils.h"

EnemyHit::EnemyHit():mnoptrCollider(nullptr), mDamage(0), mPos(Vec2D::Zero) {
	mnoptrCollider = std::make_unique<Collider2D>();
}

void EnemyHit::SetPosition(const Vec2D& pos) {
	mPos = pos;
	if (mnoptrCollider) {
		mnoptrCollider->SetPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}

void EnemyHit::SetDimensions(int w, int h, float scale) {
	if (mnoptrCollider) {
		mnoptrCollider->SetDimensions(w, h, scale);
	}
}

bool EnemyHit::IsHitting(GameEntity& target) {
	if (mnoptrCollider) {
	
	if (mnoptrCollider->IsColliding(*target.GetCollider2D(0))) {	
		return true;
	}
	}
	return false;
}

void EnemyHit::SetDamage(float damage) {
	mDamage = damage;
}

void EnemyHit::Render() {

	if (mnoptrCollider) {
		mnoptrCollider->Render();
	}

	SDL_RenderPresent(Engine::GetInstance()->GetRender());
}