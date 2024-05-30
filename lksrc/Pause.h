#pragma once

#include "GameState.h"
#include "Engine.h"

class Pause : public GameState {
public:
	Pause() { id = "pause"; };
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