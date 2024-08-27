#pragma once

#include "Managers/GameEntity.h"
#include "Collision/Collider2D.h"
#include "Physics/Vec2D.h"
#include "Entities/Enemies/Enemy.h"

class PlayerHit {
public:
	PlayerHit(GameEntity* mOwn);
	void SetPosition(const Vec2D& pos);
	void SetDimensions(int w, int h, float scale = SCALE);
	void SetDamage(float damage);
	Enemy* IsHitting();
	void Render();
	inline float GetDamage() const{ return mDamage; }

private:
	float mDamage;
	std::unique_ptr<Collider2D> mnoptrCollider;
	Vec2D mPos;
	GameEntity* mOwn;
};