#pragma once

#include "GameState.h"
#include "Button.h"


class Menu : public GameState {
public:
    Menu() {
        id = "menu";
        buttons[0] = nullptr;
        buttons[1] = nullptr;
    }
    ~Menu() override {
        Exit();
    }
    bool Init() override;
    bool Exit() override;
    void Update() override;
    void Render() override;

private:
    static void StartGame();
    static void Settings();
    static void Editor();
    static void Quit();
    Button* buttons[2];
};