#include <iostream>
#include "Menu.h"
#include "Engine.h"

bool Menu::Init() {
    mRender = Engine::GetInstance()->GetRender();

    buttons[0] = new Button("assets/images/buttonPlay.png", 100, 100, FORMAT_PNG, 1);
    buttons[0]->SetPressableTexture("assets/images/buttonPlayPressed.png", FORMAT_PNG, 1);
    buttons[0]->SetButtonFunction([]() {
        Engine::GetInstance()->ChangeState("play");
        });

    buttons[1] = new Button("assets/images/buttonQuit.png", 100, 100, FORMAT_PNG, 1);
    buttons[1]->SetPressableTexture("assets/images/buttonQuitPressed.png", FORMAT_PNG, 1);
    buttons[1]->SetButtonFunction([]() {
        Engine::GetInstance()->CloseEngine();
        });

    for (int i = 0; i < 2; i++) {
        buttons[i]->SetPosition((Engine::GetInstance()->GetWidth() / 2) - (buttons[i]->GetWidth() / 2),
            (Engine::GetInstance()->GetHeight() / 2) - 50 + (150 * i));
    }

    std::cout << "menu initialized." << std::endl;
    return true;
}

void Menu::Render() {
    for (int i = 0; i < 2; i++) {
        if (buttons[i]) {
            buttons[i]->Render();
        }
    }
}

void Menu::Update() {
    for (int i = 0; i < 2; i++) {
        if (buttons[i]) {
            buttons[i]->Update();
        }
    }
}

bool Menu::Exit() {
    for (int i = 0; i < 2; i++) {
        if (buttons[i]) {
            delete buttons[i];
            buttons[i] = nullptr;
        }
    }
    std::cout << "exit menu" << std::endl;
    return true;
}

//callbacks
void Menu::StartGame() {
    std::cout << "menu start game" << std::endl;
}

void Menu::Editor() {
    std::cout << "menu editor" << std::endl;
}

void Menu::Settings() {
    std::cout << "menu settings" << std::endl;
}

void Menu::Quit() {
    std::cout << "menu quit" << std::endl;
}