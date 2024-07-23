#include "GameStates/Play.h"
#include "Map/MapParser.h"
#include "Managers/EntityManager.h"
#include "Managers/TextureManager.h"
#include "Camera/Camera.h"
#include "Collision/Collisor.h"
#include "Core/Input.h"
#include "Entities/Player.h"
#include "Entities/Enemies/Zombie.h"

Play::Play() {
	id = "play";
}

bool Play::Init() {
	//mEditMode = false;
	Engine::GetInstance()->ShowCursor(false);
	mRender = Engine::GetInstance()->GetRender();

	TextureManager::GetInstance()->Load("background", "assets/maps/background.png");

	Register<Player> registerPlayer("PLAYER", false);
	Register<Zombie> registerZombie("ZOMBIE");
	EntityManager::GetInstance()->CreateEntityType("PLAYER");
	EntityManager::GetInstance()->ParseEntities("assets/maps/objectsLevel1");

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
	TextureManager::GetInstance()->Render("background", 0, 0, 2541, 798, 1, 1, 1.2f, true);
	mLevelMap->Render();
	EntityManager::GetInstance()->RenderAllEntities();

}

bool Play::Exit() {

	std::cout << "exit play" << std::endl;
	return true; 
}