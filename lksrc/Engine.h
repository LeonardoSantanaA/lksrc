#pragma once

#include <SDL.h>
#include <functional>

class Engine {
public:
	Engine(const char* windowName);

	~Engine();

	void SetEventCallback(std::function<void(void)> func);

	void SetRenderCallback(std::function<void(void)> func);

	void RunLoop();

	SDL_Renderer* GetRender() const;

	inline void CloseEngine() { mGameIsRunning = false; }
	inline int GetMouseX() const { return mMouseX; }
	inline int GetMouseY() const { return mMouseY; }

private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRender = nullptr;
	bool mGameIsRunning = false;
	std::function<void(void)> mEventCallback;
	std::function<void(void)> mRenderCallback;

	int mMouseX, mMouseY;

};