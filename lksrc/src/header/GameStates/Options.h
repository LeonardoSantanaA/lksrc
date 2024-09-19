#pragma once

#include "Core/GameState.h"
#include "Core/Button.h"
#include "Graphics/Font.h"
#include "Graphics/TexturedRectangle.h"

class Options : public GameState {
public:
    Options() {
        id = "options";
        textMusicTitle = nullptr;
        textMusicValue = nullptr;
        textSoundEffectsTitle = nullptr;
        textSoundEffectsValue = nullptr;
    }
    ~Options() override {
        Exit();
    }
    bool Init() override;
    bool Exit() override;
    void Update() override;
    void Render() override;

private:
    std::unique_ptr<TexturedRectangle> modalSoundEffects;
    std::unique_ptr<TexturedRectangle> modalMusic;
    std::unique_ptr<Button> buttons[5];

    Font* textMusicTitle;
    Font* textMusicValue;

    Font* textSoundEffectsTitle;
    Font* textSoundEffectsValue;

};