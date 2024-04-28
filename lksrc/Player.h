#pragma once

#include "GameEntity.h"

class Player : public GameEntity {
public:
	Player();
	Player(const std::string& name, SDL_Renderer* render);

	virtual void Update() override;
	//virtual void Render() override;
	void ChangeDirection(const char* dir);
	
private:
	bool isMoving;
	const char* mDirection;
	float mVelocity;
};