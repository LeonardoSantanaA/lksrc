#include "Player.h"
#include "EntityManager.h"

Player::Player(const std::string& name, SDL_Renderer* render): GameEntity::GameEntity(name, render){
	std::cout << "chamando construtor de player" << std::endl;

	//AddTexturedRectangleComponent("assets/images/mario.png", 0xFF, 0x00, 0xFF, FORMAT_PNG);
	AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	AddAnimation("idle", 0, 12);
	ChangeAnimation("idle");
	AddCollider2D();
	//AddCollider2D();
	SetDimensions(32, 32, 3);
	SetDebugMode(true);

	//SetPosition(50, 150, 1, 5, 30);
	GetCollider2D(0)->SetDimensions(49, 63);
	SetOffsetPositionCollision(0, 17, 30);
	SetPosition(50, 150);
	//GetCollider2D(1)->SetDimensions(80, 80);
	
	SetAnimationSpeed(10.0f);
	SetAnimationLoop(true);
}

void Player::Update() {
	//std::cout << "minha posicao: " << GetX() << std::endl;
	GameEntity::UpdateSpriteSheet();
	GameEntity::Update();


}

