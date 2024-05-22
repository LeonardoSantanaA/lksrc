
#include <iostream>
#include <string>
#include <vector>
#include <memory>

//sdl
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//glad opengl
#include <glad/glad.h>

//my includes
#include "TexturedRectangle.h"
#include "ResourceManager.h"
#include "AnimatedSprite.h"
#include "Engine.h"
#include "Font.h"
#include "GameEntity.h"
#include "Sound.h"
#include "EntityManager.h"
#include "Player.h"
#include "Input.h"
#include "TextureManager.h"
#include "GameMap.h"
#include "MapParser.h"
#include "Camera.h"
#include "Play.h"
#include "Menu.h"

//global variables
Engine* engine; 
//Font* font;
//Player* player;



std::string spriteName;

int s;
int m;

void HandleEvents() {
	

}

void HandleUpdate() {
	EntityManager::GetInstance()->UpdateAllEntities();
	//player->Update();
	Camera::GetInstance()->Update();


	//get entities
	/*
	std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
	std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");


	if (entity) {
		entity->UpdateSpriteSheet();
	}
	

	static int posX = 0;
	static int posY = 0;
	static bool up = 0;
	static bool right = 0;
	static float angle = 0;
	
	if (entity2) {
		entity2->GetX() > engine->GetWidth() ? right = false : NULL;
		entity2->GetX() < 0 ? right = true : NULL;
		entity2->GetY() < 0 ? up = false : NULL;
		entity2->GetX() > engine->GetHeight() ? up = true : NULL;
	}
	

	angle++;
	entity2->SetAngleRotate(angle);

	if (up) {
		//posY--;
	}
	else {
		//posY++;
	}

	if (right) {
		//posX++;
	}
	else {
		//posX--;
	}

	if (entity2) {
		entity2->SetPosition(850, 100);
		entity2->SetDimensions(100, 100, 1);
	}
	*/

}

void HandleRendering() {
	//Draw here

	EntityManager::GetInstance()->RenderAllEntities();
	
}

uint32_t mCallbackFun(uint32_t interval, void* param) {
	std::cout << "callbackfunction: " << (const char*)param << std::endl;
	return 0;
}

int main(int argc, char* argv[]) {

	engine = Engine::GetInstance();
	engine->Init();
	engine->SetMaxFrameRate(60);
	engine->SetEventCallback(HandleEvents);
	engine->SetUpdateCallback(HandleUpdate);
	engine->SetRenderCallback(HandleRendering);
	
	engine->AddTimer(2000, mCallbackFun, (char*)"timer called");
	
	Menu* menu = new Menu();
	Play* play = new Play();
	engine->PushState(menu);
	engine->PushState(play);
	engine->ChangeState("play");



	//get entities
	/*
	std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
	std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");

	//object1 = new TexturedRectangle(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	//entity->AddTexturedRectangleComponent("assets/images/megaman.bmp");
	entity->AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	entity->SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	entity->AddAnimation("idle", 0, 12);
	entity->AddAnimation("run", 32, 7);
	entity->ChangeAnimation("idle");
	
	entity->SetDimensions(100, 100, 1);
	entity->AddCollider2D();
	entity->AddCollider2D();
	entity->GetCollider2D(0)->SetDimensions(70, 90);
	entity->GetCollider2D(1)->SetDimensions(100, 100);
	entity->SetPosition(200, 100);
	entity->SetDebugMode(true);
	entity->SetAnimationSpeed(10.0f);
	entity->SetAnimationLoop(true);
	entity->SetOffsetPositionCollision(0, 15, 25);
	
	entity2->AddTexturedRectangleComponent("assets/images/mario.png", 0xFF, 0x00, 0xFF, FORMAT_PNG);
	entity2->AddCollider2D();
	entity2->SetDimensions(64, 64, 2);
	entity2->SetDebugMode(true);
	*/

	//font = new Font("assets/fonts/VCR_OSD_MONO.ttf", "lksrc", 58);
	//font->SetColor({ 255, 0, 255 });
	//*font = "hello world! lksrc.";
	//font->SetPosition(50, 50);


	s = Sound::GetInstance()->LoadSound("assets/snd/GameOver.wav");
	m = Sound::GetInstance()->LoadMusic("assets/snd/TetrisSoundTrack.wav");
	Sound::GetInstance()->PlayMusic(m);

	engine->RunLoop();
	
	//delete font;
	//delete player;
	delete menu;
	delete play;
	delete engine;
	

	return 0;
}
