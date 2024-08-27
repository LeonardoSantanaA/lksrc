#pragma once

#include "Managers/GameEntity.h"
#include "Entities/Enemies/Enemy.h"

class Wolf : public Enemy {
public:
	Wolf(const std::string& name);
	virtual void Attack() override;
	virtual ~Wolf() override {};

private:

};
