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

//global variables
Engine* engine; 
//TexturedRectangle* object1;
GameEntity* entity;
GameEntity* entity2;
//TexturedRectangle* object2;
Font* font;

void HandleEvents() {
	SDL_Event event;

	//start event loop
	while (SDL_PollEvent(&event)) {
		//handle each especific event

		switch (event.type) {
		case SDL_QUIT:
			engine->CloseEngine();
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
				std::cout << "mouse button left. single-click." << std::endl;
				std::cout << "x: " << engine->GetMouseX() << std::endl;
				std::cout << "y: " << engine->GetMouseY() << std::endl;

				if (entity->IsColliding(*entity2)) {
					std::cout << "colliding" << std::endl;
				}
				else {
					std::cout << "not colliding." << std::endl;
				}

			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 2) {
				std::cout << "mouse button left. double-click." << std::endl;
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 3) {
			}

			if (event.button.button == SDL_BUTTON_RIGHT) {
				std::cout << "mouse button right." << std::endl;

			}
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				std::cout << "mouse scroll button." << std::endl;
			}
			if (event.button.button == SDL_BUTTON_X1) {
				std::cout << "mouse button x1." << std::endl;
			}
			if (event.button.button == SDL_BUTTON_X2) {
				std::cout << "mouse button x2." << std::endl;
			}
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				std::cout << "esc!" << std::endl;
			}

			std::cout << "key pressed - key scancode: " << SDL_GetScancodeName(event.key.keysym.scancode) << std::endl;
			std::cout << "key pressed - key name: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
		}
	}

}

void HandleUpdate() {
	font->SetPosition(80, 50);

	entity->Update();
	entity2->Update();

	static int posX = 0;
	static int posY = 0;
	static bool up = 0;
	static bool right = 0;

	entity2->SetPosition(posX, posY);
	entity->SetPosition(engine->GetMouseX(), engine->GetMouseY());

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

	entity2->GetX() > engine->GetWidth() ? right = false : NULL;
	entity2->GetX() < 0 ? right = true : NULL;
	entity2->GetY() < 0 ? up = false : NULL;
	entity2->GetX() > engine->GetHeight() ? up = true : NULL;
}

void HandleRendering() {
	//Draw here


	font->Render(engine->GetRender());

	//object1->Render(engine->GetRender());
	entity->Render();
	entity2->Render();

}

int main(int argc, char* argv[]) {
	const char* title = "lksrc - prototype";

	engine = new Engine(title);
	engine->SetEventCallback(HandleEvents);
	engine->SetUpdateCallback(HandleUpdate);
	engine->SetRenderCallback(HandleRendering);
	engine->SetMaxFrameRate(60);

	//object1 = new TexturedRectangle(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	entity = new GameEntity(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	entity->SetDebugMode(true);

	entity2 = new GameEntity(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	entity2->SetDimensions(64, 64, 1.5f);
	entity2->SetDebugMode(true);

	font = new Font(engine->GetRender(), "assets/fonts/VCR_OSD_MONO.ttf", "lksrc", 58);
	font->SetColor(engine->GetRender(), { 255, 0, 255 });
	*font = "hello world! lksrc.";

	engine->RunLoop();

	delete engine;
	//delete object1;
	//delete object2;
	delete font;
	delete entity;
	delete entity2;

	return 0;
}
