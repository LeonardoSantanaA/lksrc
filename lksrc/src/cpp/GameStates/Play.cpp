#include "GameStates/Play.h"
#include "Map/MapParser.h"
#include "Managers/EntityManager.h"
#include "Managers/TextureManager.h"
#include "Camera/Camera.h"
#include "Collision/Collisor.h"
#include "Core/Input.h"
#include "Entities/Player.h"
#include "Entities/Enemies/Zombie.h"
#include "Entities/Enemies/Wolf.h"
#include "Entities/Enemies/Skeleton.h"
#include "Entities/Enemies/Dead.h"
#include "Entities/Enemies/DeadFire.h"
#include "Core/Sound.h"

Play::Play() {
	id = "play";
}

bool Play::Init() {
	Engine::GetInstance()->ShowCursor(false);
	mRender = Engine::GetInstance()->GetRender();

	TextureManager::GetInstance()->Load("background_1", "assets/maps/backgroundLayer1.png");
	TextureManager::GetInstance()->Load("background_2", "assets/maps/backgroundLayer2.png");
	TextureManager::GetInstance()->Load("background_3", "assets/maps/backgroundLayer3.png");

	Register<Player> registerPlayer("PLAYER", true);
	Register<Zombie> registerZombie("ZOMBIE");
	Register<Wolf> registerWolf("WOLF");
	Register<Skeleton> registerSkeleton("SKELETON");
	Register<Dead> registerDead("DEAD");
	Register<DeadFire> registerDeadFire("DEADFIRE", true);

	EntityManager::GetInstance()->CreateEntityType("PLAYER");
	EntityManager::GetInstance()->ParseEntities("assets/maps/objectsLevel1");

	if (!MapParser::GetInstance()->Load("mapDemo")) {
		std::cout << "failed to load map." << std::endl;
	}
	mLevelMap = MapParser::GetInstance()->GetMap("mapDemo");

	mGUI = std::make_unique<PlayerGUI>();

	auto& mapLayers = mLevelMap->GetMapLayers();
	TileLayer* mCollisionLayer = dynamic_cast<TileLayer*>(mapLayers.back().get());

	Collisor::GetInstance()->SetCollisionLayer(mCollisionLayer);

	Camera::GetInstance()->SetZoom(2.0f);

	int music = Sound::GetInstance()->LoadMusic("assets/snd/musics/playSoundtrack.mp3");
	Sound::GetInstance()->PlayMusic(music);

	std::cout << "play initialized" << std::endl;

	return true;
}

void Play::Update() {
	mLevelMap->Update();

	EntityManager::GetInstance()->UpdateAllEntities();
	Camera::GetInstance()->Update();

}

void Play::Render() {
	TextureManager::GetInstance()->Render("background_1", 0, 0, 320, 180, 5.0f, 5.0f, 1.1f, true);
	TextureManager::GetInstance()->Render("background_2", 0, 400, 320, 131, 3.0f, 3.0f, 1.15f, true);
	TextureManager::GetInstance()->Render("background_3", 0, 500, 320, 30, 5.0f, 5.0f, 1.2f, true);
	mLevelMap->Render();
	mGUI->Render();
	EntityManager::GetInstance()->RenderAllEntities();
}

bool Play::Exit() {
	std::cout << "exit play" << std::endl;
	return true; 
}