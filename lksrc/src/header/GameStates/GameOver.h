#pragma once

#include "Core/GameState.h"
#include "Core/Engine.h"
#include "Core/Button.h"
#include "Graphics/Font.h"

class GameOver : public GameState {
public:
	GameOver()
	{
		id = "gameover";
	};
	virtual bool Init() override;
	virtual bool Exit() override;
	virtual void Update() override;
	virtual void Render() override;

private:

	std::unique_ptr<Font> mnoptrGameOverFont;
	std::unique_ptr<Font> mnoptrReplayFont;
	std::unique_ptr<Button> mnoptrOkButton;
	std::unique_ptr<Button> mnoptrNoButton;

	static void StartGame();
	static void Quit();

};