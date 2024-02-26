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

//global variables
Engine* engine; 
TexturedRectangle* object1;
//TexturedRectangle* object2;
Font* font;
Font* font2;
Font* font3;

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

				//if (object2->IsColliding(*object1)) {
					//std::cout << "colliding" << std::endl;
				//}
				//else {
					//std::cout << "not colliding." << std::endl;
				//}

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

void HandleRendering() {

	//Draw here
	object1->Draw(90, 90, 10, 10, 8);
	font->Draw(80, 50);
	font2->Draw(100, 250);
	font3->Draw(150, 170);

	font->Render(engine->GetRender());
	font2->Render(engine->GetRender());
	font3->Render(engine->GetRender());

	object1->Render(engine->GetRender());

}

int main(int argc, char* argv[]) {
	const char* title = "lksrc - prototype";

	engine = new Engine(title);
	engine->SetEventCallback(HandleEvents);
	engine->SetRenderCallback(HandleRendering);

	object1 = new TexturedRectangle(engine->GetRender(), "assets/images/mario.png", FORMAT_PNG);
	//object2 = new TexturedRectangle(*object1);
	font = new Font(engine->GetRender(), "assets/fonts/VCR_OSD_MONO.ttf", "lksrc", 58);
	font->SetColor(engine->GetRender(), { 255, 0, 255 });
	*font = "hello world! lksrc.";

	font2 = new Font(*font);
	font2->SetColor(engine->GetRender(), { 0, 255, 255 });
	font2->SetSize(65);
	font3 = new Font(engine->GetRender(), "assets/fonts/VCR_OSD_MONO.ttf", "lksrc", 58);
	*font3 = "lksrc!";

	engine->RunLoop();

	delete engine;
	delete object1;
	//delete object2;
	delete font;
	delete font2;
	delete font3;

	return 0;
}
