#pragma once

#include "GameEntity.h"

class Player : public GameEntity {
public:
	Player(const std::string& name);

	virtual void Update() override;
	//virtual void Render() override;
	void ChangeDirection(const char* dir);
	
private:
	bool isMoving;
	const char* mDirection;
	float mVelocity;
};