#pragma once

#include <SDL.h>
#include <functional>
#include <set>
#include "Input.h"
#include "GameMap.h"

#define SCALE 4

class Engine {
public:
	static Engine* GetInstance();

	//initialize the engine
	void Init();

	~Engine();

	inline void SetWindowName(const char* name) { SDL_SetWindowTitle(mWindow, name); }
	void SetEventCallback(std::function<void(void)> func);
	void SetUpdateCallback(std::function<void(void)> func);
	void SetRenderCallback(std::function<void(void)> func);

	void RunLoop();

	inline void SetMaxFrameRate(int fr) { mMaxFrameRate = fr; }

	SDL_Renderer* GetRender() const;

	inline void CloseEngine() { mGameIsRunning = false; }
	inline int GetMouseX() const { return mMouseX; }
	inline int GetMouseY() const { return mMouseY; }

	inline void SetWidth(int w) { mWidth = w; }
	inline void SetHeight(int h) { mHeight = h; }
	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }
	inline SDL_Window* GetWindow() {
		if (mWindow) { return mWindow; }
		return nullptr;
}
	inline std::shared_ptr<GameMap> GetLevelMap() { return mLevelMap; }


	SDL_TimerID AddTimer(uint32_t delay, SDL_TimerCallback callback, void* param);
	SDL_TimerID AddRecurringTimer(uint32_t interval, SDL_TimerCallback callback, void* param);
	void RemoveTimer(SDL_TimerID id);

private:
	Engine();
	static Engine* mInstance;
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRender = nullptr;
	std::shared_ptr<GameMap> mLevelMap = std::make_shared<GameMap>();
	bool mGameIsRunning = false;
	std::function<void(void)> mEventCallback;
	std::function<void(void)> mUpdateCallback;
	std::function<void(void)> mRenderCallback;

	int mMouseX, mMouseY;
	int mWidth, mHeight;
	int mMaxFrameRate;

	std::set<SDL_TimerID> mTimers;

};