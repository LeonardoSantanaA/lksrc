#include "Player.h"
#include "EntityManager.h"
#include "Input.h"
#include "Collisor.h"
#include "Utils.h"
#include "Camera.h"
#include "EntityManager.h"

Player::Player(const std::string& name): GameEntity::GameEntity(name), 
mDirection("right"), mVelocity(3), isMoving(false), vSpd(0), grvt(.8f), canJump(false), isJumping(false), onGround(false), delayJump(0){
	int scale = 2.5f;
	AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 12);
	AddAnimation("run", 32, 7);
	AddAnimation("jumpUp", 160, 1);
	AddAnimation("jumpDown", 192, 1);
	ChangeAnimation("idle");
	AddCollider2D();
	AddCollider2D();
	SetDimensions(32, 32, scale);
	SetDebugMode(true); //turn on debug mode to see collisors

	GetCollider2D(0)->SetDimensions(16 * scale, 20 * scale);
	SetOffsetPositionCollision(0, 8 * scale, 11* scale);

	GetCollider2D(1)->SetDimensions(16 * scale, 15 * scale);
	SetOffsetPositionCollision(1, 8 * scale, 11 * scale);

	SetPosition(200, 0);
	SetAnimationLoop(true);
	Camera::GetInstance()->SetTarget(GetPoint());
}

void Player::Update() {
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();
	Gravity();
	AnimationState();


	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !IsHorizontalColliding("left")) {
		MovePosition(-mVelocity, 0);
		ChangeDirection("left");
		if (onGround) {
			isMoving = true;
		}

	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && !IsHorizontalColliding("right")) {
		MovePosition(mVelocity, 0);
		ChangeDirection("right");
		if (onGround) {
			isMoving = true;
		}
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && canJump) {
		Jump();
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
		if (delayJump >= 20) {
			canJump = true;
		}
		onGround = true;
		isJumping = false;
		vSpd = 0;
	}
	else {
		canJump = false;
		
	}

	if (delayJump <= 20) {
		delayJump++;
		if (delayJump < 20) {
			canJump = false;
		}
	}

	MovePosition(0, vSpd);

}

bool Player::IsHorizontalColliding(const char* dir) {

	if (dir == "left") {
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

void Player::Jump() {
	if (canJump) {
		isJumping = true;
		delayJump = 0;
		vSpd = -15;
		if (!Collisor::GetInstance()->PlaceFree(
			GetCollider2D(1)->GetColliderBoundingBox()->x,
			GetCollider2D(1)->GetColliderBoundingBox()->y - 1,
			GetCollider2D(1)->GetColliderBoundingBox()->w,
			GetCollider2D(1)->GetColliderBoundingBox()->h)) {
			vSpd = 1;
		}
	}

}

void Player::AnimationState() {
	if (!isMoving && !isJumping) {
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
	}
	if (isMoving) {
		this->ChangeAnimation("run");
		SetAnimationSpeed(5.0f);
		SetAnimationLoop(true);
	}
	if (isJumping) {
		isMoving = false;
		if (vSpd <= 0) {
			ChangeAnimation("jumpUp");
			SetAnimationSpeed(1);
			SetAnimationLoop(false);
		}
		else {
			ChangeAnimation("jumpDown");
			SetAnimationSpeed(2);
			SetAnimationLoop(true);
		}	
		
	}
	
}