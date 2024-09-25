
#include "Core/Engine.h"

#include <iostream>
#include <SDL.h>
#include <functional>
#include "Managers/EntityManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/TextureManager.h"
#include "Core/Sound.h"
#include "Core/Input.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"
#include "Collision/Collisor.h"

//states
#include "GameStates/Menu.h"
#include "GameStates/Play.h"

Engine* Engine::mInstance = nullptr;

Engine::Engine(): mMouseX(0), mMouseY(0), mWidth(1280), mHeight(720), mMaxFrameRate(60), mCurrentState(nullptr), mCurrentStatePoped(nullptr){

}

Engine* Engine::GetInstance() {
	if (!mInstance) {
		mInstance = new Engine;
		SDL_Log("new engine instance.");
	}
	return mInstance;
}

void Engine::Init() {
	mGameIsRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not be initialized: %s", SDL_GetError());
	}
	else {
		SDL_Log("SDL initialized.");
	}

	SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	mWindow = SDL_CreateWindow("lksrc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, windowFlags); //| SDL_WINDOW_OPENGL);)
	if (mWindow == NULL) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
	}

	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Engine::~Engine() {
	Sound::GetInstance()->QuitMixer();
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

void Engine::PopState() {
	if (mCurrentState) {
		mCurrentState->isPop = !mCurrentState->isPop;
		std::cout << "pop state" << std::endl;
	}
}

void Engine::PopState(const std::string& key) {
	for (auto state : mStates) {
		if (state->id == key) {
			//doesn`t exists a current state poped
			if (!mCurrentStatePoped) {
			
				mCurrentState->isPop = true;
				mCurrentStatePoped = state;
				mCurrentStatePoped->Init();
				std::cout << "paused" << std::endl;
			}
			else {
				mCurrentStatePoped->Exit();
				mCurrentStatePoped = nullptr;
				mCurrentState->isPop = false;
				
				std::cout << "unpaused" << std::endl;
			}
		
			break;
		}
	}
}

void Engine::PushState(GameState* current) {
	bool canPush = true;
	//verify if can push new state
	for (auto state : mStates) {
		if (state->id == current->id) {
			canPush = false;
			break;
		}
	}

	if (canPush) {
		mStates.push_back(current);
		std::cout << "adding new game state, key " << current->id << std::endl;
	}
}

void Engine::ChangeState(const std::string& idTarget) {
	bool canChange = false;
	for (auto state : mStates) {
		if (state->id == idTarget) {
			if (mCurrentState) {
				mCurrentState->Exit();
				canChange = true;
				ResourceManager::GetInstance()->ClearResourceManager();
				EntityManager::GetInstance()->DeleteAllEntities();
				TextureManager::GetInstance()->Clean();
				MapParser::GetInstance()->Clean();
				Sound::GetInstance()->QuitMixer();
				Input::GetInstance()->DestroyInput();
				Collisor::GetInstance()->Clean();

				Camera::GetInstance()->Reset();
			}
			mCurrentState = state;
			mCurrentState->Init();
		}
	}

	if (canChange) {
		std::cout << "changing game state to " << idTarget << std::endl;;
	}
	else {
		std::cout << "failed to changing game state to " << idTarget << std::endl;;
	}
}

void Engine::RunLoop() {
	const uint64_t frameDelay = 1000 / mMaxFrameRate;
	uint64_t lastTime = SDL_GetTicks64();
	uint64_t currentTime, elapsedTime;

	while (mGameIsRunning) {
		currentTime = SDL_GetTicks64();
		elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		uint32_t buttons;

		int mouseWindowX, mouseWindowY;
		buttons = SDL_GetMouseState(&mouseWindowX, &mouseWindowY);

		int windowWidth, windowHeight;
		SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &windowWidth, &windowHeight);

		const int logicalWidth = mWidth;
		const int logicalHeight = mHeight;

		float scaleX = static_cast<float>(windowWidth) / logicalWidth;
		float scaleY = static_cast<float>(windowHeight) / logicalHeight;

		mMouseX = static_cast<int>(mouseWindowX / scaleX);
		mMouseY = static_cast<int>(mouseWindowY / scaleY);

		Input::GetInstance()->Listen();
		if (mCurrentState && !mCurrentState->isPop) {
			mCurrentState->Update();
		}
		if (mCurrentStatePoped) {
			mCurrentStatePoped->Update();
		}

		SDL_SetRenderDrawColor(mRender, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mRender);
		if (mCurrentState) {
			mCurrentState->Render();
		}
		if (mCurrentStatePoped) {
			mCurrentStatePoped->Render();
		}
		SDL_RenderPresent(mRender);

		uint64_t frameTime = SDL_GetTicks64() - currentTime;

		if (frameTime < frameDelay) {
			SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
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