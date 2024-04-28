#include "Player.h"
#include "EntityManager.h"
#include "Input.h"

Player::Player(const std::string& name, SDL_Renderer* render): GameEntity::GameEntity(name, render), mDirection("right"), mVelocity(2){
	std::cout << "chamando construtor de player" << std::endl;

	//AddTexturedRectangleComponent("assets/images/mario.png", 0xFF, 0x00, 0xFF, FORMAT_PNG);
	AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 12);
	ChangeAnimation("idle");
	AddAnimation("run", 32, 7);
	AddCollider2D();
	SetDimensions(32, 32, 3);
	//SetDebugMode(true); //turn on debug mode to see collisors

	GetCollider2D(0)->SetDimensions(49, 63);
	SetOffsetPositionCollision(0, 17, 30);
	SetPosition(50, 150);

	
	SetAnimationLoop(true);
}

void Player::Update() {
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();

	if (isMoving) {
		this->ChangeAnimation("run"); 
		SetAnimationSpeed(5.0f);
	}
	else {
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		MovePosition(-mVelocity, 0);
		isMoving = true;
		ChangeDirection("left");
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		MovePosition(mVelocity, 0);
		isMoving = true;
		ChangeDirection("right");
	}
	if (!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		isMoving = false;
	}

}

void Player::ChangeDirection(const char* dir) {
	if (mDirection != dir) {
		FlipHorizontal();
		mDirection = dir;
	}
}