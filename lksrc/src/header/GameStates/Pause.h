#pragma once

#include "Core/GameState.h"
#include "Core/Engine.h"
#include "Core/Button.h"
#include "Graphics/Font.h"

class Pause : public GameState {
public:
	Pause(): mnoptrButtonContinue(nullptr), mnoptrButtonMenu(nullptr), mnoptrButtonOptions(nullptr)
	{ id = "pause"; };
	virtual bool Init() override;
	virtual bool Exit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::unique_ptr<Font> mnoptrPauseFont;
	std::unique_ptr<Button> mnoptrButtonContinue;
	std::unique_ptr<Button> mnoptrButtonMenu;
	std::unique_ptr<Button> mnoptrButtonOptions;

	static void StartGame();
	static void Quit();

};