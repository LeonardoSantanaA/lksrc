#pragma once

#include <SDL.h>

class Input {
public:
    static Input* GetInstance();
    ~Input();
    void DestroyInput();
    void Update();
    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    bool GetKeyPress(SDL_Scancode key);
    bool GetKeyRelease(SDL_Scancode key);

    bool GetMouseButtonDown(Uint8 button);
    bool GetMouseButtonPress(Uint8 button);

private:
    Input();
    static Input* mInstance;
    const Uint8* mKeyStates;
    Uint8 mPrevKeyStates[SDL_NUM_SCANCODES];

    Uint32 mMouseStates;
    Uint32 mPrevMouseStates;

    void KeyUp();
    void KeyDown();
    void MouseButtonUp();
    void MouseButtonDown();
};