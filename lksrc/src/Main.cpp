
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
#include "GameStates/GameOver.h"

//global variables
Engine* engine; 
//Font* font;
//Player* player;

//int s;
//int m;

//void HandleEvents() {
//	
//
//}
//
//void HandleUpdate() {
//	//EntityManager::GetInstance()->UpdateAllEntities();
//	//player->Update();
//	//Camera::GetInstance()->Update();
//}
//
//
//void HandleRendering() {
//	//Draw here
//
//	//EntityManager::GetInstance()->RenderAllEntities();
//	
//}
//
//
//uint32_t mCallbackFun(uint32_t interval, void* param) {
//	std::cout << "callbackfunction: " << (const char*)param << std::endl;
//	return 0;
//}


int main(int argc, char** argv) {

	engine = Engine::GetInstance();
	engine->Init();
	engine->SetWindowName("LkSouls");
	engine->SetMaxFrameRate(60);
	//engine->SetEventCallback(HandleEvents);
	//engine->SetUpdateCallback(HandleUpdate);
	//engine->SetRenderCallback(HandleRendering);
	
	//engine->AddTimer(2000, mCallbackFun, (char*)"timer called");
	
	Menu* menu = new Menu();
	Play* play = new Play();
	Pause* pause = new Pause();
	GameOver* gameOver = new GameOver();
	engine->PushState(menu);
	engine->PushState(play);
	engine->PushState(pause);
	engine->PushState(gameOver);

	engine->ChangeState("menu");

	engine->RunLoop();
	
	//delete font;
	//delete player;
	delete menu;
	delete play;
	delete pause;
	delete engine;
	delete gameOver;
	

	return 0;
}
