#include <iostream>
#include <memory>
#include <cstring>
#include "Core/Input.h"
#include "Managers/GameEntity.h"
#include "Managers/EntityManager.h"
#include "Core/Engine.h"
#include "Camera/Camera.h"

Input* Input::mInstance = nullptr;

Input* Input::GetInstance() {
    if (!mInstance) {
        mInstance = new Input;
        std::cout << "new input instance." << std::endl;
    }
    return mInstance;
}

void Input::DestroyInput() {
    if (mInstance) {
        delete mInstance;
        mInstance = nullptr;
    }
    std::cout << "input cleared." << std::endl;
}

Input::Input() {
    // Inicializa os estados do teclado
    mKeyStates = SDL_GetKeyboardState(nullptr);

    // Inicializa os estados do mouse
    mMouseStates = SDL_GetMouseState(nullptr, nullptr);
    mPrevMouseStates = mMouseStates;

    // Inicializa mPrevKeyStates com 0
    std::fill(std::begin(mPrevKeyStates), std::end(mPrevKeyStates), 0);
}

Input::~Input() {
    //DestroyInput();
}

void Input::Update() {
    std::memcpy(mPrevKeyStates, mKeyStates, SDL_NUM_SCANCODES);
    mKeyStates = SDL_GetKeyboardState(nullptr);

    mPrevMouseStates = mMouseStates;
    mMouseStates = SDL_GetMouseState(nullptr, nullptr);
}

void Input::Listen() {
    SDL_Event event;

    Update();

    //start event loop
    while (SDL_PollEvent(&event)) {
        //handle each specific event
        switch (event.type) {
        case SDL_QUIT:
            Engine::GetInstance()->CloseEngine();
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                int width = 0, height = 0;
                SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &width, &height);
                Camera::GetInstance()->Reload();
                SDL_RenderSetLogicalSize(Engine::GetInstance()->GetRender(), Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight());
            }
            break;

        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0) {
                std::cout << "scroll up." << std::endl;
            }
            else if (event.wheel.y < 0) {
                std::cout << "scroll down." << std::endl;
            }
            if (event.wheel.x > 0) {
                std::cout << "scroll right." << std::endl;
            }
            else if (event.wheel.x < 0) {
                std::cout << "scroll left." << std::endl;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            MouseButtonDown();
            if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 1) {
            }
            else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 2) {
                //std::cout << "mouse button left. double-click." << std::endl;
            }
            else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 3) {
            }

            if (event.button.button == SDL_BUTTON_RIGHT) {
               // std::cout << "mouse button right." << std::endl;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
               // std::cout << "mouse scroll button." << std::endl;
            }
            if (event.button.button == SDL_BUTTON_X1) {
               // std::cout << "mouse button x1." << std::endl;
            }
            if (event.button.button == SDL_BUTTON_X2) {
                //std::cout << "mouse button x2." << std::endl;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            MouseButtonUp();
            break;

        case SDL_KEYDOWN:
            KeyDown();
            break;

        case SDL_KEYUP:
            KeyUp();
            break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key) {
    return (mKeyStates[key] == 1);
}

bool Input::GetKeyPress(SDL_Scancode key) {
    return (mKeyStates[key] == 1 && mPrevKeyStates[key] == 0);
}

bool Input::GetKeyRelease(SDL_Scancode key) {
    return (mKeyStates[key] == 0);
}

bool Input::GetMouseButtonDown(Uint8 button) {
    return (mMouseStates & SDL_BUTTON(button)) != 0;
}

bool Input::GetMouseButtonPress(Uint8 button) {
    return ((mMouseStates & SDL_BUTTON(button)) != 0) && ((mPrevMouseStates & SDL_BUTTON(button)) == 0);
}

void Input::KeyUp() {
    mKeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown() {
    mKeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::MouseButtonUp() {
    mMouseStates = SDL_GetMouseState(nullptr, nullptr);
}

void Input::MouseButtonDown() {
    mMouseStates = SDL_GetMouseState(nullptr, nullptr);
}