#include "Player.h"
#include "EntityManager.h"
#include "Input.h"
#include "Collisor.h"
#include "Utils.h"

Player::Player(const std::string& name): GameEntity::GameEntity(name), mDirection("right"), mVelocity(3), isMoving(false), vSpd(0), grvt(.8f){
	std::cout << "chamando construtor de player" << std::endl;

	rectTest = {};
	int scale = 3;
	AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 12);
	ChangeAnimation("idle");
	AddAnimation("run", 32, 7);
	AddCollider2D();
	AddCollider2D();
	SetDimensions(32, 32, 3);
	//SetDebugMode(true); //turn on debug mode to see collisors

	GetCollider2D(0)->SetDimensions(16 * scale, 20 * scale);
	SetOffsetPositionCollision(0, 8 * scale, 11* scale);

	GetCollider2D(1)->SetDimensions(16 * scale, 17 * scale);
	SetOffsetPositionCollision(1, 8 * scale, 11 * scale);

	SetPosition(200, 0);

	SetAnimationLoop(true);
}

void Player::Update() {
	
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();
	Gravity();

	if (isMoving) {
		this->ChangeAnimation("run"); 
		SetAnimationSpeed(5.0f);
	}
	else {
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
	}


	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !IsHorizontalColliding("left")) {
		MovePosition(-mVelocity, 0);
		isMoving = true;
		ChangeDirection("left");
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && !IsHorizontalColliding("right")) {
		MovePosition(mVelocity, 0);
		isMoving = true;
		ChangeDirection("right");
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
		MovePosition(0, -10);
	}

	if ((!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)))	{
		isMoving = false;
	}	

	
}

void Player::ChangeDirection(const char* dir) {
	if (mDirection != dir) {
		FlipHorizontal();
		mDirection = dir;
	}
}

void Player::Gravity() {
	vSpd = vSpd + grvt;
	if (!Collisor::GetInstance()->PlaceFree(
		GetCollider2D(1)->GetColliderBoundingBox()->x,
		GetCollider2D(1)->GetColliderBoundingBox()->y + vSpd,
		GetCollider2D(1)->GetColliderBoundingBox()->w,
		GetCollider2D(1)->GetColliderBoundingBox()->h)) {
		while (Collisor::GetInstance()->PlaceFree(
			GetCollider2D(1)->GetColliderBoundingBox()->x,
			GetCollider2D(1)->GetColliderBoundingBox()->y + Sign(vSpd),
			GetCollider2D(1)->GetColliderBoundingBox()->w,
			GetCollider2D(1)->GetColliderBoundingBox()->h)) {
			MovePosition(0, Sign(vSpd));
		}
		vSpd = 0;
	}
	MovePosition(0, vSpd);

}

bool Player::IsHorizontalColliding(const char* dir) {

	if (dir == "left") {
		rectTest.x = GetCollider2D(1)->GetColliderBoundingBox()->x - mVelocity;
		rectTest.y = GetCollider2D(1)->GetColliderBoundingBox()->y ;
		rectTest.w = GetCollider2D(1)->GetColliderBoundingBox()->w;
		rectTest.h = GetCollider2D(1)->GetColliderBoundingBox()->h;
		if (!Collisor::GetInstance()->PlaceFree(
			GetCollider2D(1)->GetColliderBoundingBox()->x - mVelocity,
			GetCollider2D(1)->GetColliderBoundingBox()->y,
			GetCollider2D(1)->GetColliderBoundingBox()->w ,
			GetCollider2D(1)->GetColliderBoundingBox()->h)) {
			while (Collisor::GetInstance()->PlaceFree(
				GetCollider2D(1)->GetColliderBoundingBox()->x - mVelocity,
				GetCollider2D(1)->GetColliderBoundingBox()->y , 
				GetCollider2D(1)->GetColliderBoundingBox()->w, 
				GetCollider2D(1)->GetColliderBoundingBox()->h)) {
				MovePosition(mVelocity, 0);
			}
			return true;
		}
	}else if (dir == "right") {
		rectTest.x = GetCollider2D(1)->GetColliderBoundingBox()->x + mVelocity;
		rectTest.y = GetCollider2D(1)->GetColliderBoundingBox()->y;
		rectTest.w = GetCollider2D(1)->GetColliderBoundingBox()->w;
		rectTest.h = GetCollider2D(1)->GetColliderBoundingBox()->h;
		if (!Collisor::GetInstance()->PlaceFree(
			GetCollider2D(1)->GetColliderBoundingBox()->x + mVelocity,
			GetCollider2D(1)->GetColliderBoundingBox()->y,
			GetCollider2D(1)->GetColliderBoundingBox()->w, 
			GetCollider2D(1)->GetColliderBoundingBox()->h)) {
			while (Collisor::GetInstance()->PlaceFree(
				GetCollider2D(1)->GetColliderBoundingBox()->x + mVelocity,
				GetCollider2D(1)->GetColliderBoundingBox()->y ,
				GetCollider2D(1)->GetColliderBoundingBox()->w, 
				GetCollider2D(1)->GetColliderBoundingBox()->h)) {
				MovePosition(-mVelocity, 0);
			}
			return true;
		}
	}




	
	return false;
}