#pragma once

#include "Core/GameState.h"
#include "Map/GameMap.h"
#include "Managers/GameEntity.h"

class Play : public GameState {
public:
	Play();
	~Play() { mLevelMap.reset(); };
	virtual bool Init() override;
	virtual bool Exit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	//bool mEditMode;
	std::shared_ptr<GameMap> mLevelMap = std::make_shared<GameMap>();
	std::vector<GameEntity*> mGameEntities;

	//static void OpenMenu();
	//static void PauseGame();
};