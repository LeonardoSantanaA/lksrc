
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
#include "Transform.h"

//global variables
Engine* engine; 
Font* font;

std::string spriteName;

int s;
int m;

void HandleEvents() {
	SDL_Event event;

	//start event loop
	while (SDL_PollEvent(&event)) {
		//handle each especific event

		switch (event.type) {
		case SDL_QUIT:
			engine->CloseEngine();
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				int width = 0, height = 0;
				SDL_GetWindowSize(engine->GetWindow(), &width, &height);
				engine->SetWidth(width);
				engine->SetHeight(height);
				SDL_RenderSetLogicalSize(engine->GetRender(), engine->GetWidth(), engine->GetHeight());

				std::shared_ptr<GameEntity> background = EntityManager::GetInstance()->GetEntityRef("background");

				background->SetDimensions(engine->GetWidth(), engine->GetHeight(), 1);
				
			}
			break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) {
				std::cout << "scroll up." << std::endl;
			}
			else if (event.wheel.y < 0) {
				std::cout << "scroll down." << std::endl;
			}
			if (event.wheel.x > 0) {
				std::cout << "scroll right." << std::endl;
			}
			else if (event.wheel.x < 0) {
				std::cout << "scroll left." << std::endl;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 1) {
				//get entities
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");

				std::cout << "mouse button left. single-click." << std::endl;
				std::cout << "x: " << engine->GetMouseX() << std::endl;
				std::cout << "y: " << engine->GetMouseY() << std::endl;

				if (entity && entity2) {
					if (entity->IsColliding(*entity2, 0, 0)) {
						std::cout << "colliding hitbox 1" << std::endl;
						*font = "hey! colliding.";
					}
					else {
						std::cout << "not colliding hitbox 1." << std::endl;
					}
				}
				

			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 2) {
				std::cout << "mouse button left. double-click." << std::endl;
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 3) {
			}

			if (event.button.button == SDL_BUTTON_RIGHT) {
				std::cout << "mouse button right." << std::endl;
				EntityManager::GetInstance()->RemoveEntity("entity1");
			}
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				std::cout << "mouse scroll button." << std::endl;
				std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");
				entity2->FlipHorizontal();
			}
			if (event.button.button == SDL_BUTTON_X1) {
				std::cout << "mouse button x1." << std::endl;
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				if (entity) {
					entity->ChangeAnimation("idle");
				}
				
			}
			if (event.button.button == SDL_BUTTON_X2) {
				std::cout << "mouse button x2." << std::endl;
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				if (entity) {
					entity->ChangeAnimation("run");
				}
				
			}
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				std::cout << "esc!" << std::endl;
				Sound::GetInstance()->PlaySound(s);
				*font = "hey! you pressed the esc button. are you sure? my name is leo";
			}

			std::cout << "key pressed - key scancode: " << SDL_GetScancodeName(event.key.keysym.scancode) << std::endl;
			std::cout << "key pressed - key name: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
		}
	}

}

void HandleUpdate() {
	EntityManager::GetInstance()->UpdateAllEntities();

	//get entities
	std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
	std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");

	entity->UpdateSpriteSheet();

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
		posY--;
	}
	else {
		posY++;
	}

	if (right) {
		posX++;
	}
	else {
		posX--;
	}

	if (entity2) {
		entity2->SetPosition(posX, posY);
		entity2->SetDimensions(100, 100, 1);
	}


	if (entity) {
		entity->SetPosition(engine->GetMouseX(), engine->GetMouseY(), 0, 15, 4);
	}
	

}

void HandleRendering() {
	//Draw here
	EntityManager::GetInstance()->RenderAllEntities();
	font->Render(engine->GetRender());
	std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
	if (entity) {
		entity->Render(spriteName, false, 7.0f);
	}
	
}

uint32_t mCallbackFun(uint32_t interval, void* param) {
	std::cout << "callbackfunction: " << (const char*)param << std::endl;
	return 0;
}

int main(int argc, char* argv[]) {

	engine = new Engine("lksrc - prototype");
	engine->SetMaxFrameRate(60);
	engine->SetEventCallback(HandleEvents);
	engine->SetUpdateCallback(HandleUpdate);
	engine->SetRenderCallback(HandleRendering);

	engine->AddTimer(2000, mCallbackFun, (char*)"timer called");
	
	//create entities
	EntityManager::GetInstance()->CreateEntity("entity1", engine->GetRender());
	EntityManager::GetInstance()->CreateEntity("entity2", engine->GetRender());
	EntityManager::GetInstance()->CreateEntity("background", engine->GetRender(), Layer::BACKGROUND);

	//get entities
	std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
	std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");
	std::shared_ptr<GameEntity> background = EntityManager::GetInstance()->GetEntityRef("background");

	//object1 = new TexturedRectangle(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	//entity->AddTexturedRectangleComponent("assets/images/megaman.bmp");
	entity->AddAnimatedSprite("assets/images/spriteSheetPlayer.png", FORMAT_PNG);
	entity->SetAnimatedSpriteDimensionsInSpriteSheet(32, 32);
	entity->AddAnimation("idle", 0, 12);
	entity->AddAnimation("run", 32, 7);
	entity->ChangeAnimation("idle");
	
	entity->SetAnimatedSpriteDimensions(80, 80);
	//entity->SetDimensions(100, 100, 1);
	entity->AddCollider2D();
	entity->AddCollider2D();
	entity->GetCollider2D(0)->SetDimensions(70, 90);
	entity->GetCollider2D(1)->SetDimensions(100, 100);
	entity->SetDebugMode(true);
	entity->SetAnimationSpeed(40.0f);
	entity->SetAnimationLoop(true);
	
	entity2->AddTexturedRectangleComponent("assets/images/mario.png", 0xFF, 0x00, 0xFF, FORMAT_PNG);
	entity2->AddCollider2D();
	entity2->SetDimensions(64, 64, 2);
	entity2->SetDebugMode(true);

	std::cout << "width:" << engine->GetWidth() << std::endl;
	background->AddTexturedRectangleComponent("assets/images/tom.bmp", FORMAT_BMP);
	background->SetPosition(0, 0);
	background->SetDimensions(engine->GetWidth(), engine->GetHeight(), 1);

	font = new Font(engine->GetRender(), "assets/fonts/VCR_OSD_MONO.ttf", "lksrc", 58);
	font->SetColor(engine->GetRender(), { 255, 0, 255 });
	*font = "hello world! lksrc.";
	font->SetPosition(50, 50);

	s = Sound::GetInstance()->LoadSound("assets/snd/GameOver.wav");
	m = Sound::GetInstance()->LoadMusic("assets/snd/TetrisSoundTrack.wav");
	Sound::GetInstance()->PlayMusic(m);

	Transform tf;
	tf.Log();

	engine->RunLoop();

	
	delete font;
	delete engine;


	return 0;
}
