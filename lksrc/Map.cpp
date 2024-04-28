#include "Map.h"

void Map::Update() {
	for (unsigned int i = 0; i < mMapLayers.size(); i++) {
		mMapLayers[i]->Update();
	}
}

void Map::Render() {
	for (unsigned int i = 0; i < mMapLayers.size(); i++) {
		mMapLayers[i]->Render();
	}
}