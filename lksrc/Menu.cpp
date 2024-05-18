#include <iostream>
#include "Menu.h"
#include "Engine.h"


bool Menu::Init() {
	mRender = Engine::GetInstance()->GetRender();
	std::cout << "menu initialized." << std::endl;
	return true;
}

void Menu::Render() {
	SDL_SetRenderDrawColor(mRender, 16, 54, 70, 255);
	SDL_RenderClear(mRender);

	SDL_RenderPresent(mRender);
}

void Menu::Update() {

}

bool Menu::Exit() {
	std::cout << "exit menu" << std::endl;
	return true;
}

//callbacks
void Menu::StartGame() {
	std::cout << "menu start game" << std::endl;
}

void Menu::Editor() {
	std::cout << "menu editor" << std::endl;
}

void Menu::Settings() {
	std::cout << "menu settings" << std::endl;
}

void Menu::Quit() {
	std::cout << "menu quit" << std::endl;
}