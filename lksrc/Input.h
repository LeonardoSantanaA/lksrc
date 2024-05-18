#pragma once

#include "SDL.h"

class Input {
public:
	static Input* GetInstance();
	~Input();
	void DestroyInput();
	void Update();
	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyPress(SDL_Scancode key);

private:
	Input();
	static Input* mInstance;
	const Uint8* mKeyStates;
	Uint8 mPrevKeyStates[SDL_NUM_SCANCODES];
	void KeyUp();
	void KeyDown();

};