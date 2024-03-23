#pragma once

#include "Engine.h"

#include <iostream>
#include <SDL.h>
#include <functional>
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Sound.h"

Engine::Engine(const char* windowName): mMouseX(0), mMouseY(0), mWidth(800), mHeight(600), mMaxFrameRate(60) {
	mGameIsRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
	Sound::QuitMixer();
	ResourceManager::GetInstance()->ClearResourceManager();
	EntityManager::GetInstance()->DeleteAllEntities();
	Sound::GetInstance()->ClearSound();
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

SDL_TimerID Engine::AddTimer(uint32_t delay, SDL_TimerCallback callback, void* param) {
	SDL_TimerID id = SDL_AddTimer(delay, callback, param);
	mTimers.insert(id);
	return id;
}

SDL_TimerID Engine::AddRecurringTimer(uint32_t interval, SDL_TimerCallback callback, void* param) {
	SDL_TimerID id = SDL_AddTimer(interval, callback, param);
	mTimers.insert(id);

	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return (interval);
}

void Engine::RemoveTimer(SDL_TimerID id) {
	auto search = mTimers.find(id);
	if (search != mTimers.end()) {
		if (SDL_RemoveTimer(id) == SDL_FALSE) {
			std::cout << "timer not removed." << std::endl;
		}
		else {
			mTimers.erase(id);
		}
	}
	else {
		std::cout << "timer not found.engine::removetimer()." << std::endl;
	}
}