#include <iostream>
#include "GameStates/Pause.h"
#include "Core/Engine.h"
#include "Entities/Player.h"
#include "Managers/EntityManager.h"

bool Pause::Init() {
	std::cout << "pause initialized." << std::endl;
	mRender = Engine::GetInstance()->GetRender();

	mnoptrPauseFont = std::make_unique<Font>("assets/fonts/VCR_OSD_MONO.ttf", "Pause", 30);
	mnoptrPauseFont->SetPosition(Engine::GetInstance()->GetWidth() / 2 - mnoptrPauseFont->GetSize() / 2, static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrPauseFont->GetSize() / 2) - 30.0f);

	mnoptrButtonContinue = std::make_unique<Button>("assets/images/pause/buttonGoPause.png", 16, 16, FORMAT_PNG, 5.0f);
	mnoptrButtonContinue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>((mnoptrButtonContinue->GetWidth() / 2)) - 80.0f,
		static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrButtonContinue->GetHeight() / 2));
	mnoptrButtonContinue->SetPressableTexture("assets/images/pause/buttonGoPausePressed.png", FORMAT_PNG, 5.2f);
	mnoptrButtonContinue->SetButtonFunction([this]() {
		StartGame();
		});

	mnoptrButtonMenu = std::make_unique<Button>("assets/images/pause/buttonExitPause.png", 16, 16, FORMAT_PNG, 5.0f);
	mnoptrButtonMenu->SetPosition(static_cast<float>((Engine::GetInstance()->GetWidth() / 2)) - static_cast<float>((mnoptrButtonMenu->GetWidth() / 2)) + 40.0f,
		static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrButtonMenu->GetHeight() / 2));
	mnoptrButtonMenu->SetPressableTexture("assets/images/pause/buttonExitPausePressed.png", FORMAT_PNG, 5.2f);
	mnoptrButtonMenu->SetButtonFunction([]() {
		Engine::GetInstance()->PopState("pause");
		Engine::GetInstance()->ChangeState("menu");
		});

	mnoptrButtonOptions = std::make_unique<Button>("assets/images/pause/buttonConfigVolume.png", 16, 16, FORMAT_PNG, 5.0f);
	mnoptrButtonOptions->SetPosition(static_cast<float>((Engine::GetInstance()->GetWidth() - 100)),
		 20);
	mnoptrButtonOptions->SetPressableTexture("assets/images/pause/buttonConfigVolumePressed.png", FORMAT_PNG, 5.2f);
	mnoptrButtonOptions->SetButtonFunction([]() {
		Engine::GetInstance()->PopState("pause");
		Engine::GetInstance()->PopState("optionsPause");
		});

	Engine::GetInstance()->ShowCursor(true);
	return true;
}

void Pause::Render() {
	mnoptrPauseFont->Render();
	mnoptrButtonContinue->Render();
	mnoptrButtonMenu->Render();
	mnoptrButtonOptions->Render();
}

void Pause::Update() {
	mnoptrPauseFont->SetPosition(Engine::GetInstance()->GetWidth() / 2 - mnoptrPauseFont->GetSize() / 2, static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrPauseFont->GetSize() / 2) - 30.0f);

	mnoptrButtonContinue->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth() / 2) - static_cast<float>((mnoptrButtonContinue->GetWidth() / 2)) - 80.0f,
			static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrButtonContinue->GetHeight() / 2));
	mnoptrButtonContinue->Update();

	mnoptrButtonMenu->SetPosition(static_cast<float>((Engine::GetInstance()->GetWidth() / 2)) - static_cast<float>((mnoptrButtonMenu->GetWidth() / 2)) + 40.0f,
			static_cast<float>(Engine::GetInstance()->GetHeight() / 2) - static_cast<float>(mnoptrButtonMenu->GetHeight() / 2));
	mnoptrButtonMenu->Update();

	mnoptrButtonOptions->SetPosition(static_cast<float>((Engine::GetInstance()->GetWidth() - 100)),
		20);
	mnoptrButtonOptions->Update();
}

bool Pause::Exit() {
	Engine::GetInstance()->ShowCursor(false);

	std::cout << "exit pause" << std::endl;
	return true;
}

//callbacks
void Pause::StartGame() {
	Engine::GetInstance()->PopState("pause");
	std::cout << "pause start game" << std::endl;
}

void Pause::Quit() {
	std::cout << "pause quit" << std::endl;
}