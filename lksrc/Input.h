#pragma once

#include "SDL.h"

class Input {
public:
	static Input* GetInstance();
	~Input();
	void DestroyInput();
	void Listen();
	bool GetKeyDown(SDL_Scancode key);

private:
	static Input* mInstance;
	const Uint8* mKeyStates;
	Input();
	void KeyUp();
	void KeyDown();
	

};