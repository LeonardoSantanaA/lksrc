#pragma once

#include "Engine.h"

#include <iostream>
#include <SDL.h>
#include <functional>
#include "ResourceManager.h"

Engine::Engine(const char* windowName): mMouseX(0), mMouseY(0), mWidth(800), mHeight(600), mMaxFrameRate(60) {
	mGameIsRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "SDL could not be initialized: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "SDL initialized." << std::endl;
	}

	mWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_RESIZABLE); //| SDL_WINDOW_OPENGL);)
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

void Engine::SetUpdateCallback(std::function<void(void)> func) {
	mUpdateCallback = func;
}

void Engine::SetRenderCallback(std::function<void(void)> func) {
	mRenderCallback = func;
}

void Engine::RunLoop() {
	uint64_t lastTime = 0, elapsedTime;

	while (mGameIsRunning) {
		uint64_t start = SDL_GetTicks64();

		uint32_t buttons;
		buttons = SDL_GetMouseState(&mMouseX, &mMouseY);
		mEventCallback();
		mUpdateCallback();

		SDL_SetRenderDrawColor(mRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mRender);
		//Draw
		mRenderCallback();

		//TODO: set a frame cap

		//show what draw
		SDL_RenderPresent(mRender);

		elapsedTime = SDL_GetTicks64() - start;

		uint64_t waitTime = (1 / (double)mMaxFrameRate) * 1000;

		if (elapsedTime < waitTime) {
			SDL_Delay(waitTime - elapsedTime);
		}
	}
}

SDL_Renderer* Engine::GetRender() const {
	return mRender;
}
