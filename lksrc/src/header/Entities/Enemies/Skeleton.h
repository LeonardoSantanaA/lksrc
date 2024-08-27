#pragma once

#include "Managers/GameEntity.h"
#include "Entities/Enemies/Enemy.h"

class Skeleton : public Enemy {
public:
	Skeleton(const std::string& name);
	virtual ~Skeleton() override {};
	virtual void Attack() override;
	virtual void AnimationState() override;
private:
	bool mCanHit2;
};
