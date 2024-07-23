#pragma once

#include <SDL.h>
#include <functional>
#include <set>
#include "Core/Input.h"
#include "Map/GameMap.h"
#include "Core/GameState.h"

class Engine {
public:
	static Engine* GetInstance();

	//initialize the engine
	void Init();

	~Engine();

	//change the name of window
	inline void SetWindowName(const char* name) { SDL_SetWindowTitle(mWindow, name); }
	void SetEventCallback(std::function<void(void)> func);
	void SetUpdateCallback(std::function<void(void)> func);
	void SetRenderCallback(std::function<void(void)> func);

	//run the main loop
	void RunLoop();

	//set the max FPS
	inline void SetMaxFrameRate(int fr) { mMaxFrameRate = fr; }

	//pause the update of current game state
	void PopState();
	void PopState(const std::string& key);

	//add a new game state, follow the example:
	// 
	//class Play : public GameState
	// 
	//define in constructor the id name of game state:
	//	Play::Play() { id = "play";}
	// 
	//in the Main.cpp:
	//	Play play = new Play();
	//	Engine::GetInstance()->PushState("play");
	// 
	//don't forget to delete the play in final of Main.cpp:
	//	delete play;
	void PushState(GameState* current);

	//change the current game state
	void ChangeState(const std::string& idTarget);

	//returns the SDL_Renderer* of engine
	SDL_Renderer* GetRender() const;

	inline void CloseEngine() { mGameIsRunning = false; }
	inline int GetMouseX() const { return mMouseX; }
	inline int GetMouseY() const { return mMouseY; }

	inline void SetWidth(int w) { mWidth = w; }
	inline void SetHeight(int h) { mHeight = h; }
	inline void ShowCursor(bool enable) { SDL_ShowCursor(enable); }
	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }
	inline SDL_Window* GetWindow() {
		if (mWindow) { return mWindow; }
		return nullptr;
}
	//inline std::shared_ptr<GameMap> GetLevelMap() { return mLevelMap; }


	SDL_TimerID AddTimer(uint32_t delay, SDL_TimerCallback callback, void* param);
	SDL_TimerID AddRecurringTimer(uint32_t interval, SDL_TimerCallback callback, void* param);
	void RemoveTimer(SDL_TimerID id);

private:
	Engine();
	static Engine* mInstance;
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRender = nullptr;
	//std::shared_ptr<GameMap> mLevelMap = std::make_shared<GameMap>();
	bool mGameIsRunning = false;
	std::function<void(void)> mEventCallback;
	std::function<void(void)> mUpdateCallback;
	std::function<void(void)> mRenderCallback;

	int mMouseX, mMouseY;
	int mWidth, mHeight;
	int mMaxFrameRate;

	std::set<SDL_TimerID> mTimers;
	std::vector<GameState*> mStates;
	GameState* mCurrentState;
	GameState* mCurrentStatePoped;

};