#include "Entities/Player.h"
#include "Managers/EntityManager.h"
#include "Core/Input.h"
#include "Collision/Collisor.h"
#include "Managers/Utils.h"
#include "Camera/Camera.h"
#include "Managers/EntityManager.h"

Player::Player(const std::string& name) : GameEntity::GameEntity(name),
mDirection("right"), mVelocity(0), isMoving(false), vSpd(0), grvt(.8f), canJump(false), isJumping(false), onGround(false), delayJump(0), maxMoveDelay(5.0f), moveDelay(0), mMaxVelocity(3),
mStepVelocity(0.2f), mFactorVelocity(1.0f), inChangeDirection(false), isAttacking(false), currentIndexAttack(0), currentDelayAttack(0), maxDelayAttack(30.0f), 
nameCurrentAnimationAttack("attack_0"), currentDelayComboAttack(0), maxDelayComboAttack(50.0f), canChangeDirection(true), delayCanChangeDirection(10)
{
	float scale = 1.5f;
	AddAnimatedSprite("assets/images/player.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(120, 80);
	AddAnimation("idle", 0, 10);
	AddAnimation("run", 160, 10);
	AddAnimation("jumpUp", 240, 2);
	AddAnimation("jumpDown", 320, 3);
	AddAnimation("changingPosition", 80, 3);
	AddAnimation("attack_0", 560, 4);
	AddAnimation("attack_1", 640, 6);
	ChangeAnimation("idle");
	AddCollider2D();
	AddCollider2D();
	SetDimensions(120, 80, scale);
	//SetDebugMode(true); //turn on debug mode to see collisors

	GetCollider2D(0)->SetDimensions(static_cast<int>(20), static_cast<int>(38), scale);
	SetOffsetPositionCollision(0, static_cast<int>(50),  static_cast<int>(42), scale);

	GetCollider2D(1)->SetDimensions(static_cast<int>(20), static_cast<int>(30), scale);
	SetOffsetPositionCollision(1, static_cast<int>(50), static_cast<int>(42), scale);

	SetPosition(200, 0);
	SetAnimationLoop(true);
	Camera::GetInstance()->SetTarget(GetPoint());
}

void Player::Update() {
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();
	Gravity();
	AnimationState();
	HorizontalMovement();

	if (!isMoving || isAttacking){
		ResetVelocity();
	}

	if (onGround) {
		isMoving = true;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && canChangeDirection) {
			ChangeDirection("left");
	}else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && canChangeDirection) {
			ChangeDirection("right");
	}
	
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && canJump) {
		Jump();
	}

	if ((!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)))	{
		isMoving = false;
		inChangeDirection = false;
	}

	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) && !isJumping && !isAttacking) {
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
		isMoving = false;
		inChangeDirection = false;
		ResetVelocity();
	}

	if (Input::GetInstance()->GetMouseButtonPress(SDL_BUTTON_LEFT)) {
		Attack();
	}

}

void Player::ChangeDirection(const char* dir) {
	if (!isAttacking) {
		if (!StringCompare(mDirection, dir)) {
			inChangeDirection = true;
			canJump = false;
			ResetVelocity();
			if (IsLastFrame() && !isJumping) {
				FlipHorizontal();
				mDirection = dir;
				inChangeDirection = false;
				canJump = true;
			}
		}

		if (StringCompare(dir, "right") && !inChangeDirection) {
			if (mVelocity <= mMaxVelocity) {
				mVelocity += mStepVelocity;
			}
			if (mVelocity > mMaxVelocity) {
				mVelocity = mMaxVelocity;
			}
		}
		if (StringCompare(dir, "left") && !inChangeDirection) {
			if (mVelocity >= -mMaxVelocity) {
				mVelocity -= mStepVelocity;
			}
			if (mVelocity < -mMaxVelocity) {
				mVelocity = -mMaxVelocity;
			}
		}
	}


}

void Player::Gravity() {
	vSpd = vSpd + grvt;
	if (!Collisor::GetInstance()->PlaceFree(
		GetCollider2D(1)->GetColliderBoundingBox()->x,
		static_cast<int>(GetCollider2D(1)->GetColliderBoundingBox()->y + vSpd),
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

	MovePosition(0.0f, vSpd);

}

bool Player::HorizontalMovement() {
	if (delayCanChangeDirection < 5) {
		delayCanChangeDirection++;
		canChangeDirection = false;
	}
	else {
		delayCanChangeDirection = 5;
		canChangeDirection = true;
	}

		if (!Collisor::GetInstance()->PlaceFree(
			static_cast<int>(GetCollider2D(1)->GetColliderBoundingBox()->x + mVelocity),
			GetCollider2D(1)->GetColliderBoundingBox()->y,
			GetCollider2D(1)->GetColliderBoundingBox()->w,
			GetCollider2D(1)->GetColliderBoundingBox()->h)) {
			while (Collisor::GetInstance()->PlaceFree(
				GetCollider2D(1)->GetColliderBoundingBox()->x + Sign(mVelocity),
				GetCollider2D(1)->GetColliderBoundingBox()->y,
				GetCollider2D(1)->GetColliderBoundingBox()->w,
				GetCollider2D(1)->GetColliderBoundingBox()->h)) {
					MovePosition(Sign(mVelocity), 0);
			}
			return false;
		}
		MovePosition(mVelocity, 0.0f);

		return true;
}

void Player::Jump() {
	if (canJump && !isAttacking) {
		isJumping = true;
		delayJump = 0;
		vSpd = -12;
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
	if (currentDelayAttack < maxDelayAttack) {
		currentDelayAttack++;
		//std::cout << "delay de ataque: " << currentDelayAttack << std::endl;
	}
	if (currentIndexAttack > 0 ) {
		if (currentDelayComboAttack < maxDelayComboAttack) {
			currentDelayComboAttack++;
			//std::cout << "delay de combo: " << currentDelayComboAttack << std::endl;
		}
		else {
			currentIndexAttack = 0;
			currentDelayComboAttack = 0;
			//std::cout << "zerando index de ataque" << std::endl;
		}
		
	}


	if ((isMoving && !inChangeDirection && !isJumping && onGround && !isAttacking)) {
		this->ChangeAnimation("run");
		SetAnimationSpeed(5.0f);
		SetAnimationLoop(true);
	}
	else if (isJumping) {
		isMoving = false;
		if (vSpd <= 0) {
			ChangeAnimation("jumpUp");
			SetAnimationSpeed(10);
			SetAnimationLoop(true);
		}
		else {
			ChangeAnimation("jumpDown");
			SetAnimationSpeed(2);
			SetAnimationLoop(true);
		}
	 }
	else if (isAttacking) {
		ChangeAnimation(nameCurrentAnimationAttack);
		SetAnimationSpeed(4.0f);
		SetAnimationLoop(false);
		if (IsLastFrame()) {
			isAttacking = false;
			delayCanChangeDirection = 0;
		}
	}
	else if (inChangeDirection && !isJumping) {
		 ChangeAnimation("changingPosition");
		 canJump = false;
		 SetAnimationSpeed(6.0f);
		 SetAnimationLoop(false);
	 }
	else if (Collisor::GetInstance()->PlaceFree(
		GetCollider2D(1)->GetColliderBoundingBox()->x,
		static_cast<int>(GetCollider2D(1)->GetColliderBoundingBox()->y + 1),
		GetCollider2D(1)->GetColliderBoundingBox()->w,
		GetCollider2D(1)->GetColliderBoundingBox()->h) && !isJumping) {
	 
		 ChangeAnimation("jumpDown");
		 SetAnimationSpeed(2);
		 SetAnimationLoop(true);
	}

	else {
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
		SetAnimationLoop(true);
	
	}
}

void Player::ResetVelocity() {
	if (mVelocity > 0) {
		mVelocity -= mStepVelocity;
		if (mVelocity < 0) {
			mVelocity = 0;
		}
	}

	if (mVelocity < 0) {
		mVelocity += mStepVelocity;
		if (mVelocity > 0) {
			mVelocity = 0;
		}
	}
}

void Player::Attack() {
	//std::cout << "atacar" << std::endl;
	if (currentDelayAttack >= maxDelayAttack && !isJumping && !isAttacking) {
		if (currentIndexAttack > 1) {
			currentIndexAttack = 0;
		}
		nameCurrentAnimationAttack = "attack_" + std::to_string(currentIndexAttack);
		//std::cout << "nome ataque: " << nameCurrentAnimationAttack << std::endl;
		currentDelayComboAttack = 0;
		currentDelayAttack = 0;
		currentIndexAttack++;
		isAttacking = true;
		isMoving = false;
	}
}