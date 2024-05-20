#include "Play.h"
#include "MapParser.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Collisor.h"
#include "Input.h"
#include "Player.h"

Play::Play() {
	id = "play";
}

bool Play::Init() {
	//mEditMode = false;
	mRender = Engine::GetInstance()->GetRender();

	TextureManager::GetInstance()->Load("background", "assets/maps/background.png");

	Register<Player> registerPlayer("PLAYER");
	EntityManager::GetInstance()->CreateEntityType("PLAYER");

	if (!MapParser::GetInstance()->Load("mapDemo")) {
		std::cout << "failed to load map." << std::endl;
	}
	mLevelMap = MapParser::GetInstance()->GetMap("mapDemo");

	auto& mapLayers = mLevelMap->GetMapLayers();
	TileLayer* mCollisionLayer = dynamic_cast<TileLayer*>(mapLayers.back().get());

	Collisor::GetInstance()->SetCollisionLayer(mCollisionLayer);
	Camera::GetInstance()->SetZoom(2.0f);

	std::cout << "play initialized" << std::endl;

	return true;
}

void Play::Update() {
	mLevelMap->Update();

	EntityManager::GetInstance()->UpdateAllEntities();
	Camera::GetInstance()->Update();

}

void Play::Render() {
	TextureManager::GetInstance()->Render("background", 0, 0, 2541, 798, 2, 1, .5f);

	mLevelMap->Render();

	EntityManager::GetInstance()->RenderAllEntities();

}

bool Play::Exit() {
	MapParser::GetInstance()->Clean();
	EntityManager::GetInstance()->DeleteAllEntities();
	TextureManager::GetInstance()->Clean();
	Collisor::GetInstance()->Clean();

	std::cout << "exit play" << std::endl;
	return true; 
}