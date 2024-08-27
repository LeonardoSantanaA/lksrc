#include <iostream>
#include "GameStates/GameOver.h"
#include "Core/Engine.h"

bool GameOver::Init() {
	std::cout << "gameover initialized." << std::endl;
	mRender = Engine::GetInstance()->GetRender();

	mnoptrGameOverFont = std::make_unique<Font>("assets/fonts/VCR_OSD_MONO.ttf", "Game Over!", 30);
	mnoptrGameOverFont->SetPosition(Engine::GetInstance()->GetWidth() / 2 - mnoptrGameOverFont->GetSize() / 2, Engine::GetInstance()->GetHeight() / 2 - mnoptrGameOverFont->GetSize() / 2);
	mnoptrReplayFont = std::make_unique<Font>("assets/fonts/VCR_OSD_MONO.ttf", "Replay?", 30);

	mnoptrOkButton = std::make_unique<Button>("assets/images/gameover/okButton.png", 16, 16, FORMAT_PNG, 5.0f);
	mnoptrOkButton->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth()) / 2.0f - (mnoptrOkButton->GetWidth() / 2.0f) - 80.0f,
		static_cast<float>(Engine::GetInstance()->GetHeight()) / 2.0f - 20.0f);
	mnoptrOkButton->SetPressableTexture("assets/images/gameover/okButtonPressed.png", FORMAT_PNG, 5.2f);
	mnoptrOkButton->SetButtonFunction([]() {
		Engine::GetInstance()->PopState("gameover");
		Engine::GetInstance()->ChangeState("play");
		});

	mnoptrNoButton = std::make_unique<Button>("assets/images/gameover/noButton.png", 16, 16, FORMAT_PNG, 5.0f);
	mnoptrNoButton->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth()) / 2.0f - (mnoptrOkButton->GetWidth() / 2.0f) + 40.0f, static_cast<float>(Engine::GetInstance()->GetHeight()) / 2.0f - 20.0f);
	mnoptrNoButton->SetPressableTexture("assets/images/gameover/noButtonPressed.png", FORMAT_PNG, 5.2f);
	mnoptrNoButton->SetButtonFunction([]() {
		Engine::GetInstance()->PopState("gameover");
		Engine::GetInstance()->ChangeState("menu");
		});

	Engine::GetInstance()->ShowCursor(true);
	return true;
}

void GameOver::Render() {
		mnoptrGameOverFont->Render();
		mnoptrReplayFont->Render();
		mnoptrOkButton->Render();
		mnoptrNoButton->Render();
}

void GameOver::Update() {
	mnoptrGameOverFont->SetPosition(Engine::GetInstance()->GetWidth() / 2 - mnoptrGameOverFont->GetSize() / 2, Engine::GetInstance()->GetHeight() / 2 - mnoptrGameOverFont->GetSize() / 2);
	mnoptrReplayFont->SetPosition(Engine::GetInstance()->GetWidth() / 2 - mnoptrGameOverFont->GetSize() / 2, Engine::GetInstance()->GetHeight() / 2 - mnoptrGameOverFont->GetSize() / 2 + 40);

	mnoptrOkButton->Update();
	mnoptrOkButton->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth()) / 2.0f - (mnoptrOkButton->GetWidth() / 2.0f) - 80.0f,
		static_cast<float>(Engine::GetInstance()->GetHeight()) / 2.0f - 20.0f);

	mnoptrNoButton->Update();
	mnoptrNoButton->SetPosition(static_cast<float>(Engine::GetInstance()->GetWidth()) / 2.0f - (mnoptrOkButton->GetWidth() / 2.0f) + 40.0f, static_cast<float>(Engine::GetInstance()->GetHeight()) / 2.0f - 20.0f);

}

bool GameOver::Exit() {
	Engine::GetInstance()->ShowCursor(false);

	std::cout << "exit gameover" << std::endl;
	return true;
}

//callbacks
void GameOver::StartGame() {
	Engine::GetInstance()->PopState("gameover");
	std::cout << "gameover start game" << std::endl;
}

void GameOver::Quit() {
	std::cout << "gameover quit" << std::endl;
}