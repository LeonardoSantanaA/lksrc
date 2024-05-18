#pragma once

#include "GameState.h"

class Menu : public GameState {
public:
	Menu() { id = "menu"; };
	virtual bool Init() override;
	virtual bool Exit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	static void StartGame();
	static void Settings();
	static void Editor();
	static void Quit();

};