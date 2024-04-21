#include <iostream>
#include <memory>

#include "Input.h"
#include "GameEntity.h"
#include "EntityManager.h"
#include "Engine.h"


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
}

Input::Input() {
	mKeyStates = SDL_GetKeyboardState(nullptr);
}

Input::~Input() {
	//DestroyInput();
}

void Input::Listen() {
	SDL_Event event;

	//start event loop
	while (SDL_PollEvent(&event)) {
		//handle each especific event

		switch (event.type) {
		case SDL_QUIT:
			Engine::GetInstance()->CloseEngine();
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				int width = 0, height = 0;
				SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &width, &height);
				Engine::GetInstance()->SetWidth(width);
				Engine::GetInstance()->SetHeight(height);
				SDL_RenderSetLogicalSize(Engine::GetInstance()->GetRender(), Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight());

				std::shared_ptr<GameEntity> background = EntityManager::GetInstance()->GetEntityRef("background");

				background->SetDimensions(Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight(), 1);

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

			if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 1) {
				//get entities
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity2");

				std::cout << "mouse button left. single-click." << std::endl;
				std::cout << "x: " << Engine::GetInstance()->GetMouseX() << std::endl;
				std::cout << "y: " << Engine::GetInstance()->GetMouseY() << std::endl;

				


			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 2) {
				std::cout << "mouse button left. double-click." << std::endl;
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks == 3) {
			}

			if (event.button.button == SDL_BUTTON_RIGHT) {
				std::cout << "mouse button right." << std::endl;
				EntityManager::GetInstance()->RemoveEntity("entity1");
			}
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				std::cout << "mouse scroll button." << std::endl;
				std::shared_ptr<GameEntity> entity2 = EntityManager::GetInstance()->GetEntityRef("entity1");
				if (entity2) {
					entity2->FlipHorizontal();
				}

			}
			if (event.button.button == SDL_BUTTON_X1) {
				std::cout << "mouse button x1." << std::endl;
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				if (entity) {
					entity->ChangeAnimation("idle");
				}

			}
			if (event.button.button == SDL_BUTTON_X2) {
				std::cout << "mouse button x2." << std::endl;
				std::shared_ptr<GameEntity> entity = EntityManager::GetInstance()->GetEntityRef("entity1");
				if (entity) {
					entity->ChangeAnimation("run");
				}

			}
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

void Input::KeyUp() {
	mKeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown() {
	mKeyStates = SDL_GetKeyboardState(nullptr);
}