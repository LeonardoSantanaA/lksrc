#pragma once

#include "SDL.h"

class Input {
public:
	static Input* GetInstance();
	~Input();
	void DestroyInput();
	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyPress(SDL_Scancode key);

private:
	Input();
	static Input* mInstance;
	const Uint8* mKeyStates;
	void KeyUp();
	void KeyDown();

};