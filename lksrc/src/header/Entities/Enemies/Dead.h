#pragma once

#include "Managers/GameEntity.h"
#include "Entities/Enemies/Enemy.h"

class Dead : public Enemy {
public:
	Dead(const std::string& name);
	virtual ~Dead() override {};

	virtual void AnimationState() override;
private:
	bool mCanCreateFire;
};
