#pragma once

#include "Engine.h"

#include <iostream>
#include <SDL.h>
#include <functional>
#include "EntityManager.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "Sound.h"
#include "Input.h"
#include "MapParser.h"
#include "Camera.h"
#include "Collisor.h"

Engine* Engine::mInstance = nullptr;

Engine::Engine(): mMouseX(0), mMouseY(0), mWidth(800), mHeight(600), mMaxFrameRate(60) {

}

Engine* Engine::GetInstance() {
	if (!mInstance) {
		mInstance = new Engine;
		std::cout << "new engine instance." << std::endl;
	}
	return mInstance;
}

void Engine::Init() {
	mGameIsRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not be initialized: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "SDL initialized." << std::endl;
	}

	SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	mWindow = SDL_CreateWindow("lksrc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, windowFlags); //| SDL_WINDOW_OPENGL);)
	if (mWindow == NULL) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
	}

	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!MapParser::GetInstance()->Load("mapDemo")) {
		std::cout << "failed to load map." << std::endl;
	}
	mLevelMap = MapParser::GetInstance()->GetMap("mapDemo");
}

Engine::~Engine() {
	Sound::QuitMixer();
	ResourceManager::GetInstance()->ClearResourceManager();
	EntityManager::GetInstance()->DeleteAllEntities();
	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
	Sound::GetInstance()->ClearSound();
	Input::GetInstance()->DestroyInput();
	Camera::GetInstance()->Clean();
	Collisor::GetInstance()->Clean();
	
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
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

		Input::GetInstance()->Listen();
		mLevelMap->Update();
		mUpdateCallback();

		SDL_Event event{};

		SDL_SetRenderDrawColor(mRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mRender);
		//Draw
		mLevelMap->Render();
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