#include <iostream>
#include "GameStates/OptionsPause.h"
#include "Core/Engine.h"
#include "Core/Sound.h"

const int TOTAL_BUTTONS = 5;

bool OptionsPause::Init() {
    mRender = Engine::GetInstance()->GetRender();
    Engine::GetInstance()->ShowCursor(true);

    //button minus sound effect
    buttons[0] = std::make_unique<Button>("assets/images/menu/buttonMinus.png", 100, 100, FORMAT_PNG, 1);
    buttons[0]->SetPressableTexture("assets/images/menu/buttonMinusPressed.png", FORMAT_PNG, 1);
    buttons[0]->SetButtonFunction([]() {
        int volume = Sound::GetInstance()->GetVolumeSound();
        if (volume > 0) {
            Sound::GetInstance()->SetVolumeSound(volume - 1);
        }

        });
    buttons[0]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[0]->GetWidth() * 2),
        (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[0]->GetWidth()) / 2) + 20);

    //button minus music
    buttons[1] = std::make_unique<Button>("assets/images/menu/buttonMinus.png", 100, 100, FORMAT_PNG, 1);
    buttons[1]->SetPressableTexture("assets/images/menu/buttonMinusPressed.png", FORMAT_PNG, 1);
    buttons[1]->SetButtonFunction([]() {
        int volume = Sound::GetInstance()->GetVolumeMusic();
        if (volume > 0) {
            Sound::GetInstance()->SetVolumeMusic(volume - 1);
        }
        });
    buttons[1]->SetPosition(static_cast<float>(buttons[0]->GetPosition().x),
        static_cast<float>(buttons[0]->GetPosition().y) - buttons[0]->GetHeight() - 50);

    //buttons plus sound effect
    buttons[2] = std::make_unique<Button>("assets/images/menu/buttonPlus.png", 100, 100, FORMAT_PNG, 1);
    buttons[2]->SetPressableTexture("assets/images/menu/buttonPlusPressed.png", FORMAT_PNG, 1);
    buttons[2]->SetButtonFunction([]() {
        int volume = Sound::GetInstance()->GetVolumeSound();
        if (volume < MIX_MAX_VOLUME) {
            Sound::GetInstance()->SetVolumeSound(volume + 1);
        }
        });
    buttons[2]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) + static_cast<float>(buttons[2]->GetWidth()),
        buttons[0]->GetPosition().y);

    //buttons plus music
    buttons[3] = std::make_unique<Button>("assets/images/menu/buttonPlus.png", 100, 100, FORMAT_PNG, 1);
    buttons[3]->SetPressableTexture("assets/images/menu/buttonPlusPressed.png", FORMAT_PNG, 1);
    buttons[3]->SetButtonFunction([]() {
        int volume = Sound::GetInstance()->GetVolumeMusic();
        if (volume < MIX_MAX_VOLUME) {
            Sound::GetInstance()->SetVolumeMusic(volume + 1);
        }
        });
    buttons[3]->SetPosition(static_cast<float>(buttons[2]->GetPosition().x),
        buttons[1]->GetPosition().y);

    //button back
    buttons[4] = std::make_unique <Button>("assets/images/menu/buttonQuit.png", 100, 100, FORMAT_PNG, 1);
    buttons[4]->SetPressableTexture("assets/images/menu/buttonQuitPressed.png", FORMAT_PNG, 1);
    buttons[4]->SetButtonFunction([]() {
        Engine::GetInstance()->PopState("optionsPause");
        Engine::GetInstance()->PopState("pause");
        });
    buttons[4]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[2]->GetWidth() / 2),
        (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[2]->GetWidth()) / 2) + (85 * 2));

    //title music
    textMusicTitle = new Font("assets/fonts/VCR_OSD_MONO.ttf", "Music", 26);
    textMusicTitle->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textMusicTitle->GetSize() / 2),
        buttons[1]->GetPosition().y - 70);

    //modal music
    modalMusic = std::make_unique<TexturedRectangle>("assets/images/menu/modalVolume.png", FORMAT_PNG);
    modalMusic->SetDimensions(150, 120, 1.0f);
    modalMusic->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(modalMusic->GetWidth() / 2),
        buttons[1]->GetPosition().y - (static_cast<float>(modalMusic->GetWidth()) / 2) + 50);

    //value music
    textMusicValue = new Font("assets/fonts/VCR_OSD_MONO.ttf", std::to_string(Sound::GetInstance()->GetVolumeMusic()), 46);
    textMusicValue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textMusicValue->GetSize() / 2),
        buttons[3]->GetPosition().y - 10);

    //title sound effects
    textSoundEffectsTitle = new Font("assets/fonts/VCR_OSD_MONO.ttf", "Sound Effects", 26);
    textSoundEffectsTitle->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textSoundEffectsTitle->GetSize() / 2),
        buttons[0]->GetPosition().y - 50);

    //value sound effects
    textSoundEffectsValue = new Font("assets/fonts/VCR_OSD_MONO.ttf", std::to_string(Sound::GetInstance()->GetVolumeSound()), 46);
    textSoundEffectsValue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textSoundEffectsValue->GetSize() / 2),
        (Engine::GetInstance()->GetHeight() / 2.0f) - static_cast<float>(textSoundEffectsValue->GetHeight() / 2));

    //modal sound effect
    modalSoundEffects = std::make_unique<TexturedRectangle>("assets/images/menu/modalVolume.png", FORMAT_PNG);
    modalSoundEffects->SetDimensions(150, 120, 1.0f);
    modalSoundEffects->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(modalSoundEffects->GetWidth() / 2),
        (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(modalSoundEffects->GetWidth()) / 2) + 20);


    std::cout << "menu initialized." << std::endl;
    return true;
}

void OptionsPause::Render() {
    for (int i = 0; i < TOTAL_BUTTONS; i++) {
        if (buttons[i]) {
            buttons[i]->Render();
        }
    }

    if (textMusicTitle) {
        textMusicTitle->Render();
    }

    if (modalMusic) {
        modalMusic->Render(true);
    }

    if (modalSoundEffects) {
        modalSoundEffects->Render(true);
    }

    if (textSoundEffectsTitle) {
        textSoundEffectsTitle->Render();
    }

    if (textSoundEffectsValue) {
        textSoundEffectsValue->Render();
    }

    if (textMusicValue) {
        textMusicValue->Render();
    }
}

void OptionsPause::Update() {
    for (int i = 0; i < TOTAL_BUTTONS; i++) {
        if (buttons[i]) {
            buttons[i]->Update();
        }
    }

    if (buttons[0]) {
        buttons[0]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[0]->GetWidth() * 2),
            (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[0]->GetWidth()) / 2));
    }

    if (buttons[1]) {
        buttons[1]->SetPosition(static_cast<float>(buttons[0]->GetPosition().x),
            static_cast<float>(buttons[0]->GetPosition().y) - buttons[0]->GetHeight() - 50);
    }

    if (buttons[2]) {
        buttons[2]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) + static_cast<float>(buttons[2]->GetWidth()),
            buttons[0]->GetPosition().y);
    }

    if (buttons[3]) {
        buttons[3]->SetPosition(static_cast<float>(buttons[2]->GetPosition().x),
            buttons[1]->GetPosition().y);
    }

    if (buttons[4]) {
        buttons[4]->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(buttons[2]->GetWidth() / 2),
            (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(buttons[2]->GetWidth()) / 2) + (85 * 2));
    }

    if (textMusicTitle && buttons[1]) {
        textMusicTitle->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textMusicTitle->GetSize() / 2),
            buttons[1]->GetPosition().y - 50);
    }

    if (modalMusic) {
        modalMusic->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(modalMusic->GetWidth() / 2),
            buttons[1]->GetPosition().y - (static_cast<float>(modalMusic->GetWidth()) / 2) + 50);
    }

    if (textMusicValue) {
        textMusicValue->SetText(std::to_string(Sound::GetInstance()->GetVolumeMusic()));
        textMusicValue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textMusicValue->GetSize() / 2),
            buttons[3]->GetPosition().y + 10);
    }

    if (textSoundEffectsTitle) {
        textSoundEffectsTitle->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textSoundEffectsTitle->GetSize() / 2),
            buttons[0]->GetPosition().y - 50);
    }

    if (modalSoundEffects) {
        modalSoundEffects->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(modalSoundEffects->GetWidth() / 2),
            (Engine::GetInstance()->GetHeight() / 2.0f) - (static_cast<float>(modalSoundEffects->GetWidth()) / 2) + 20);
    }

    if (textSoundEffectsValue) {
        textSoundEffectsValue->SetText(std::to_string(Sound::GetInstance()->GetVolumeSound()));
        textSoundEffectsValue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>(textSoundEffectsValue->GetSize() / 2),
            (Engine::GetInstance()->GetHeight() / 2.0f) - static_cast<float>(textSoundEffectsValue->GetHeight() / 2));
    }


}

bool OptionsPause::Exit() {

    if (textMusicTitle) {
        delete textMusicTitle;
        textMusicTitle = nullptr;
    }

    if (textMusicValue) {
        delete textMusicValue;
        textMusicValue = nullptr;
    }

    if (textSoundEffectsTitle) {
        delete textSoundEffectsTitle;
        textSoundEffectsTitle = nullptr;
    }

    if (textSoundEffectsValue) {
        delete textSoundEffectsValue;
        textSoundEffectsValue = nullptr;
    }

    std::cout << "exit options" << std::endl;
    return true;
}

