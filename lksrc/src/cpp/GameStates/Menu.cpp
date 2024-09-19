#include <iostream>
#include "GameStates/Menu.h"
#include "Core/Engine.h"
#include "Core/Sound.h"

bool Menu::Init() {
    mRender = Engine::GetInstance()->GetRender();
    Engine::GetInstance()->ShowCursor(true);

    buttons[0] = new Button("assets/images/menu/buttonPlay.png", 100, 100, FORMAT_PNG, 1);
    buttons[0]->SetPressableTexture("assets/images/menu/buttonPlayPressed.png", FORMAT_PNG, 1);
    buttons[0]->SetButtonFunction([]() {
        Engine::GetInstance()->ChangeState("play");
        });

    buttons[1] = new Button("assets/images/menu/buttonOption.png", 100, 100, FORMAT_PNG, 1);
    buttons[1]->SetPressableTexture("assets/images/menu/buttonOptionPressed.png", FORMAT_PNG, 1);
    buttons[1]->SetButtonFunction([]() {
        Engine::GetInstance()->ChangeState("options");
        });

    buttons[2] = new Button("assets/images/menu/buttonQuit.png", 100, 100, FORMAT_PNG, 1);
    buttons[2]->SetPressableTexture("assets/images/menu/buttonQuitPressed.png", FORMAT_PNG, 1);
    buttons[2]->SetButtonFunction([]() {
        Engine::GetInstance()->CloseEngine();
        });

    for (int i = 0; i < 3; i++) {
        buttons[i]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[i]->GetWidth() / 2),
            (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[i]->GetWidth()) / 2) + (85 * i));
    }

    int music = Sound::GetInstance()->LoadMusic("assets/snd/musics/menuSoundtrack.mp3");
    Sound::GetInstance()->PlayMusic(music);

    std::cout << "menu initialized." << std::endl;
    return true;
}

void Menu::Render() {
    for (int i = 0; i < 3; i++) {
        if (buttons[i]) {
            buttons[i]->Render();
        }
    }
}

void Menu::Update() {
    for (int i = 0; i < 3; i++) {
        if (buttons[i]) {
            buttons[i]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[i]->GetWidth() / 2),
                (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[i]->GetWidth()) / 2) + (85 * i));
            buttons[i]->Update();
        }
    }
}

bool Menu::Exit() {
    for (int i = 0; i < 3; i++) {
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