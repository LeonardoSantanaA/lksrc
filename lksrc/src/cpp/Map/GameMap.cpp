#include "Map/GameMap.h"

void GameMap::Update() {
	for (unsigned int i = 0; i < mMapLayers.size(); i++) {
		mMapLayers[i]->Update();
	}
}

void GameMap::Render() {
	for (unsigned int i = 0; i < mMapLayers.size(); i++) {
		mMapLayers[i]->Render();
	}
}