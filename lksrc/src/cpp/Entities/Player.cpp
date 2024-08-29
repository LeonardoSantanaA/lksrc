#include "Entities/Player.h"
#include "Managers/EntityManager.h"
#include "Core/Input.h"
#include "Collision/Collisor.h"
#include "Managers/Utils.h"
#include "Camera/Camera.h"

//stamina cost to roll
const float ROLL_COST = 15.0f;

//horizontal dash value
const float ROLL_DASH = 8.0f;

//stamina cost to jump
const float JUMP_COST = 10.0f;

//jump height value
const float JUMP_VALUE = 12.0f;

//max delay to player jump again
const int JUMP_DELAY = 20;

//max delay to player roll again
const int ROLL_DELAY = 20;

//cost to attack defense
const float DEFENSE_COST = 15.0f;

//delay when take damage
const int DAMAGE_DELAY = 15;

//stamina cost to attack
const float ATTACK_COST = 10.0f;


Player::Player(const std::string& name) : GameEntity::GameEntity(name),
mDirection(1), mVelocity(0), isMoving(false), vSpd(0), grvt(.8f), canJump(false), isJumping(false),  delayJump(0), maxMoveDelay(5.0f), moveDelay(0), mMaxVelocity(3),
mStepVelocity(0.2f), inChangeDirection(false), isAttacking(false), currentIndexAttack(0), currentDelayAttack(0), maxDelayAttack(30.0f),
nameCurrentAnimationAttack("attack_0"), currentDelayComboAttack(0), maxDelayComboAttack(50.0f), mHit(this), canHit(true), mCurrentState(PLAYER_IDLE), canChangeDirection(false), mDelayCanChangeDirection(0), isRolling(false), canRoll(true), mDelayCanRoll(0), preparingToDefend(false), isDefending(false), canPrepareToDefend(false), takingDamage(false), mDelayTakingDamage(0), mLife(100.0f), mMaxLife(100.0f), mStepLife(0.08f), mStamina(80.0f), mMaxStamina(80.0f), mStepStamina(0.2f), isDead(false)
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
	AddAnimation("roll", 400, 12);
	AddAnimation("defense", 880, 5);
	AddAnimation("inDefense", 960, 2);
	AddAnimation("damage", 1040, 3);
	AddAnimation("dead", 480, 10);

	ChangeAnimation("idle");
	AddCollider2D();
	AddCollider2D();
	SetDimensions(120, 80, scale);
	//SetDebugMode(true); //turn on debug mode to see collisors

	GetCollider2D(0)->SetDimensions(static_cast<int>(20), static_cast<int>(38), scale);
	SetOffsetPositionCollision(0, static_cast<int>(50), static_cast<int>(42), scale);

	GetCollider2D(1)->SetDimensions(static_cast<int>(20), static_cast<int>(15), scale);
	SetOffsetPositionCollision(1, static_cast<int>(50), static_cast<int>(42), scale);

	mHit.SetDamage(3.0f);
	mHit.SetDimensions(32, 32, 1.0f);

	SetPosition(200, 0);
	SetAnimationLoop(true);
	Camera::GetInstance()->SetTarget(GetPoint());

}

void Player::Update() {
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();
	Gravity();
	InputHandle();
	HorizontalMovement();
	AnimationState();

	//std::cout << "isRolling: " << isRolling << std::endl;
	//std::cout << "canRoll: " << canRoll << std::endl;
	/*std::cout << "------------------" << std::endl;
	std::cout << "isAttacking: " << isAttacking << std::endl;
	std::cout << "canJump: " << canJump << std::endl;
	std::cout << "takingDamage: " << takingDamage << std::endl;
	std::cout << "canChangeDirection: " << canChangeDirection << std::endl;
	std::cout << "isMoving: " << isMoving << std::endl;
	std::cout << "canPrepareToDefend: " << canPrepareToDefend << std::endl;
	std::cout << "isJumping: " << isJumping << std::endl;
	std::cout << "------------------" << std::endl;*/
}

void Player::InputHandle() {
	auto input = Input::GetInstance();

	if (!isDead) {
	if (Input::GetInstance()->GetKeyPress(SDL_SCANCODE_ESCAPE)) {
		Engine::GetInstance()->PopState("pause");
	}

	if (input->GetKeyDown(SDL_SCANCODE_A)) {
		Move(-1);
	}
	else if (input->GetKeyDown(SDL_SCANCODE_D)) {
		Move(1);
	}

	if (input->GetKeyDown(SDL_SCANCODE_SPACE)) {
		Jump();
	}

	if (input->GetKeyPress(SDL_SCANCODE_LCTRL)) {
		Roll();
	}

	if (!input->GetKeyDown(SDL_SCANCODE_A) && !input->GetKeyDown(SDL_SCANCODE_D) && CanAct()) {
		isMoving = false;
		inChangeDirection = false;
		mCurrentState = PLAYER_IDLE;
	}

	if ((input->GetKeyDown(SDL_SCANCODE_A) && input->GetKeyDown(SDL_SCANCODE_D)) && CanAct()) {
		mCurrentState = PLAYER_IDLE;
		isMoving = false;
		inChangeDirection = false;
		ResetVelocity();
	}

	if (input->GetMouseButtonPress(SDL_BUTTON_LEFT)) {
		Attack();
	}

	if (input->GetMouseButtonDown(SDL_BUTTON_RIGHT)) {
		Defense();
	}
	else {
		preparingToDefend = false;
		isDefending = false;
		canPrepareToDefend = true;
	}
	}
}

void Player::Render() {
	GameEntity::Render();
}

void Player::Move(int dir) {
	if (dir != mDirection && CanAct()) {
		ChangeDirection(dir);
	}
	else {
		if (CanAct()) {
			isMoving = true;

			mCurrentState = PLAYER_RUNNING;
			mStamina += (mStepStamina / 2.0f);
			if (dir == 1) {
				if (mVelocity <= mMaxVelocity) {
					mVelocity += mStepVelocity;
				}
				if (mVelocity > mMaxVelocity) {
					mVelocity = mMaxVelocity;
				}
			}
			if (dir == -1) {
				if (mVelocity >= -mMaxVelocity) {
					mVelocity -= mStepVelocity;
				}
				if (mVelocity < -mMaxVelocity) {
					mVelocity = -mMaxVelocity;
				}
			}
		}

	}
}

void Player::Roll() {
	if (CanAct() && canRoll && mStamina >= ROLL_COST) {
		mCurrentState = PLAYER_ROLLING;
		isRolling = true;
		isMoving = false;
		mStamina -= ROLL_COST;
		if (canRoll) {
			mVelocity = ROLL_DASH * mDirection;
			canRoll = false;
		}

	}
}

void Player::ChangeDirection(int dir) {
	if (CanAct()) {
		mCurrentState = PLAYER_CHANGE_POSITION;
		canJump = false;
		ResetVelocity();
		if (IsLastFrame() && canChangeDirection && mCurrentState == PLAYER_CHANGE_POSITION) {
			FlipHorizontal();
			inChangeDirection = false;
			canJump = true;
			mDirection = dir;
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
		if (delayJump >= JUMP_DELAY) {
			canJump = true;
		}
		isJumping = false;
		vSpd = 0;
	}
	else {
		//canJump = false;
	}

	if (delayJump <= JUMP_DELAY) {
		delayJump++;
		if (delayJump < JUMP_DELAY) {
			canJump = false;
		}
	}

	MovePosition(0.0f, vSpd);
}

bool Player::HorizontalMovement() {
	if (mStamina > mMaxStamina) {
		mStamina = mMaxStamina;
	}
	if (mStamina < 0) {
		mStamina = 0;
	}

	if (mLife > mMaxLife) {
		mLife = mMaxLife;
	}


	if (!isMoving) {
		mLife += mStepLife;
		mStamina += mStepStamina;
	}

	//reset velocity if is attacking or stoped
	if (!isMoving || isAttacking) {
		ResetVelocity();
	}

	//delay for roll, change for stamina verify!
	if (mDelayCanRoll < ROLL_DELAY + ((mMaxStamina - mStamina) / 2)) {
		mDelayCanRoll++;
	}
	else {
		canRoll = true;
	}

	if (takingDamage) {
		mDelayTakingDamage++;
		if (!isDefending || mStamina < DEFENSE_COST) {
			mCurrentState = PLAYER_DAMAGE;
		}
		if (mDelayTakingDamage >= DAMAGE_DELAY) {
			takingDamage = false;
			mDelayTakingDamage = 0;

		}
	}

	//delay to change direction (dont let change position while attacking)
	if (!canChangeDirection) {
		mDelayCanChangeDirection++;
		if (mDelayCanChangeDirection >= 5) {
			canChangeDirection = true;
			mDelayCanChangeDirection = 0;
		}
	}

	//horizontal movement
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
	if (canJump && CanAct() && mStamina >= JUMP_COST) {
		canJump = false;
		isJumping = true;
		mCurrentState = PLAYER_JUMPING;
		delayJump = 0;
		mStamina -= JUMP_COST;
		vSpd = -JUMP_VALUE;
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
	//switch for animations
	switch (mCurrentState) {
	case PLAYER_IDLE:
		ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
		SetAnimationLoop(true);
		break;

	case PLAYER_RUNNING:
		ChangeAnimation("run");
		SetAnimationSpeed(5.0f);
		SetAnimationLoop(true);
		break;

	case PLAYER_ROLLING:
		ChangeAnimation("roll");
		SetAnimationSpeed(2.0f);
		SetAnimationLoop(false);
		if (IsLastFrame()) {
			mDelayCanRoll = 0;
			isRolling = false;
			mCurrentState = PLAYER_IDLE;
			canChangeDirection = false;
		}
		break;

	case PLAYER_JUMPING:
		if (vSpd <= 0) {
			ChangeAnimation("jumpUp");
			SetAnimationSpeed(10.0f);
			SetAnimationLoop(true);
		}
		else {
			ChangeAnimation("jumpDown");
			SetAnimationSpeed(2.0f);
			SetAnimationLoop(true);
		}
		break;

	case PLAYER_CHANGE_POSITION:
		ChangeAnimation("changingPosition");
		canJump = false;
		SetAnimationSpeed(6.0f);
		SetAnimationLoop(false);
		break;

	case PLAYER_ATTACKING:
	{
		ChangeAnimation(nameCurrentAnimationAttack);
		SetAnimationSpeed(4.0f);
		SetAnimationLoop(false);

		Vec2D hitPos = GetVec2D(1);
		if (GetCurrentAnimationFrame() >= 2 && GetCurrentAnimationFrame() <= 4) {
			hitPos.x += (50 * mDirection);
			mHit.SetPosition(hitPos);
			//mHit.Render(); //-> DEBUG!
			Enemy* enemyHit = mHit.IsHitting();
			if (enemyHit && canHit) {
				canHit = false;
				if (enemyHit->GetLife() > 0.0f) {
					Camera::GetInstance()->Screenshake(1.0f, 5.0f);
					enemyHit->TakeDamage(mHit.GetDamage(), *this);
				}
			}
		}

		if (IsLastFrame()) {
			isAttacking = false;
			canHit = true;
			canChangeDirection = false;
		}
	}
	break;

	case PLAYER_DEFENDING:
		canChangeDirection = false;
		if (preparingToDefend) {
			ChangeAnimation("defense");
			SetAnimationSpeed(2.0f);
			SetAnimationLoop(true);
			if (IsLastFrame()) {
				isDefending = true;
				preparingToDefend = false;
			}
		}
		else {
			ChangeAnimation("inDefense");
			SetAnimationLoop(true);
			SetAnimationSpeed(20.0f);
			
		}
		break;

	case PLAYER_DAMAGE:
		if (isDead) {
			ChangeAnimation("dead");
			SetAnimationLoop(false);
			SetAnimationSpeed(6.0f);
			if (IsLastFrame()) {
				Engine::GetInstance()->PopState("gameover");
			}
		}
		else {
			ChangeAnimation("damage");
			SetAnimationLoop(false);
			SetAnimationSpeed(8.0f);
			if (IsLastFrame()) {
				mCurrentState = PLAYER_IDLE;
				takingDamage = false;
			}
		}
	
		break;

	default:
		this->ChangeAnimation("idle");
		SetAnimationSpeed(10.0f);
		SetAnimationLoop(true);
		break;
	}

	//controls the delay to attack
	if (currentDelayAttack < maxDelayAttack) {
		currentDelayAttack++;
	}

	//controls delay for consecutive attack
	if (currentIndexAttack > 0) {
		if (currentDelayComboAttack < maxDelayComboAttack) {
			currentDelayComboAttack++;
		}
		else {
			currentIndexAttack = 0;
			currentDelayComboAttack = 0;
		}
	}

	//verify if player is falling
	if (Collisor::GetInstance()->PlaceFree(
		GetCollider2D(1)->GetColliderBoundingBox()->x,
		static_cast<int>(GetCollider2D(1)->GetColliderBoundingBox()->y + 1),
		GetCollider2D(1)->GetColliderBoundingBox()->w,
		GetCollider2D(1)->GetColliderBoundingBox()->h) && !isJumping && !isRolling && !isDead) {

		ChangeAnimation("jumpDown");
		SetAnimationSpeed(2);
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
	if (currentDelayAttack >= maxDelayAttack && CanAct() && mStamina >= ATTACK_COST && !takingDamage) {
		if (currentIndexAttack > 1) { //player has 2 attack, when current index is > 1, the index must have to back to 0
			currentIndexAttack = 0;
		}
		nameCurrentAnimationAttack = "attack_" + std::to_string(currentIndexAttack);
		currentDelayComboAttack = 0;
		currentDelayAttack = 0;
		mStamina -= ATTACK_COST;
		isAttacking = true;
		isMoving = false;
		mCurrentState = PLAYER_ATTACKING;
		currentIndexAttack++;
	}
}

void Player::Defense() {
	if (CanAct()) {
		mCurrentState = PLAYER_DEFENDING;
		isMoving = false;
		inChangeDirection = false;
		if (!takingDamage) {
			ResetVelocity();
		}
		if (canPrepareToDefend) {
			preparingToDefend = true;
			canPrepareToDefend = false;
		}
	}
}

void Player::TakeDamage(float damage, float knockback) {
	if (damage >= mLife) {
		isDead = true;
		mVelocity = 0;
		isDefending = false;
		mLife = 0;
	}
	takingDamage = true;
	isRolling = false;
	isAttacking = false;
	//canChangeDirection = false;
	//currentDelayAttack = 0;
	if (!isJumping && !isRolling) {
		if (isDefending && mStamina >= DEFENSE_COST) { //player is defending, then only receives 20% of the damage and 50% of knockback
			mStamina -= damage * 0.6f;
			damage = damage * 0.2f; 
			knockback = knockback * 0.5f;
			Camera::GetInstance()->Screenshake(1.0f, 3.0f);
		}
		Camera::GetInstance()->Screenshake(1.0f, 5.0f);
		mLife -= damage;
		mVelocity = knockback;
	}
}

bool Player::CanAct() const{
	return !isAttacking && !isJumping && !isRolling && !isDefending && !takingDamage;
}