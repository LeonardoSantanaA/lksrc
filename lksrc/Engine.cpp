#pragma once

#include "Engine.h"

#include <iostream>
#include <SDL.h>
#include <functional>
#include "ResourceManager.h"

Engine::Engine(const char* windowName): mMouseX(0), mMouseY(0) {
	mGameIsRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL coult nod be initialized: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "SDL initialized." << std::endl;
	}

	mWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE); //| SDL_WINDOW_OPENGL);)
	if (mWindow == NULL) {
			std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
	}

	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

Engine::~Engine() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
	ResourceManager::GetInstance().ClearResourceManager();
	SDL_Quit();
}

void Engine::SetEventCallback(std::function<void(void)> func) {
	mEventCallback = func;
}

void Engine::SetRenderCallback(std::function<void(void)> func) {
	mRenderCallback = func;
}

void Engine::RunLoop() {
	while (mGameIsRunning) {
		uint32_t buttons;
		buttons = SDL_GetMouseState(&mMouseX, &mMouseY);
		mEventCallback();

		SDL_SetRenderDrawColor(mRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mRender);
		//Draw
		mRenderCallback();

		//TODO: set a frame cap

		//whow what draw
		SDL_RenderPresent(mRender);
	}
}

SDL_Renderer* Engine::GetRender() const {
	return mRender;
}
