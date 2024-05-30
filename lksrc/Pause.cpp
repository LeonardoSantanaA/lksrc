#include <iostream>
#include "Pause.h"
#include "Engine.h"


bool Pause::Init() {
	mRender = Engine::GetInstance()->GetRender();
	std::cout << "menu initialized." << std::endl;
	return true;
}

void Pause::Render() {
	SDL_Rect rect;
	rect.x = 200;
	rect.y = 54;
	rect.w = 505;
	rect.h = 53;


	SDL_SetRenderDrawColor(mRender, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(mRender, &rect);
	
}

void Pause::Update() {
	if (Input::GetInstance()->GetKeyPress(SDL_SCANCODE_G)) {
		std::cout << "teste" << std::endl;
	}
}

bool Pause::Exit() {
	std::cout << "exit menu" << std::endl;
	return true;
}

//callbacks
void Pause::StartGame() {
	std::cout << "pause start game" << std::endl;
}

void Pause::Editor() {
	std::cout << "pause editor" << std::endl;
}

void Pause::Settings() {
	std::cout << "pause settings" << std::endl;
}

void Pause::Quit() {
	std::cout << "pause quit" << std::endl;
}