
#include <iostream>
#include <string>
#include <vector>
#include <memory>

//sdl
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

//glad opengl
#include <glad/glad.h>

//my includes
#include "Core/Engine.h"
#include "Graphics/TexturedRectangle.h"
#include "Managers/ResourceManager.h"
#include "Graphics/AnimatedSprite.h"
#include "Graphics/Font.h"
#include "Managers/GameEntity.h"
#include "Core/Sound.h"
#include "Managers/EntityManager.h"
#include "Entities/Player.h"
#include "Core/Input.h"
#include "Managers/TextureManager.h"
#include "Map/GameMap.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"
#include "GameStates/Play.h"
#include "GameStates/Menu.h"
#include "GameStates/Pause.h"

//global variables
Engine* engine; 
//Font* font;
//Player* player;



std::string spriteName;

//int s;
//int m;

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


int main(int argc, char** argv) {

	engine = Engine::GetInstance();
	engine->Init();
	engine->SetMaxFrameRate(60);
	engine->SetEventCallback(HandleEvents);
	engine->SetUpdateCallback(HandleUpdate);
	engine->SetRenderCallback(HandleRendering);
	
	engine->AddTimer(2000, mCallbackFun, (char*)"timer called");
	
	Menu* menu = new Menu();
	Play* play = new Play();
	Pause* pause = new Pause();
	engine->PushState(menu);
	engine->PushState(play);
	engine->PushState(pause);

	engine->ChangeState("menu");

	engine->RunLoop();
	
	//delete font;
	//delete player;
	delete menu;
	delete play;
	delete pause;
	delete engine;

	

	return 0;
}
