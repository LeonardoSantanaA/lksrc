#pragma once

#include "Managers/GameEntity.h"
#include "Entities/Enemies/Enemy.h"

class Zombie : public Enemy {
public:
	Zombie(const std::string& name);
	virtual void Update() override;

private:

}; 
