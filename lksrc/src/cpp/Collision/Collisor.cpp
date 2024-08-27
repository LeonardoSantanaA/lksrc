#include "Collision/Collisor.h"
#include "Core/Engine.h"
#include "Camera/Camera.h"
#include <iostream>

Collisor* Collisor::mInstance = nullptr;

Collisor::Collisor() : mCollisionLayer(nullptr) {
	//auto& mapLayers = Engine::GetInstance()->GetLevelMap()->GetMapLayers();
	//mCollisionLayer = dynamic_cast<TileLayer*>(mapLayers.back().get());
	
};

void Collisor::SetCollisionLayer(TileLayer* tileLayer) {
	mCollisionLayer = tileLayer;
	mCollisionTilemap = mCollisionLayer->GetTilemap();
	int tileSize = tileLayer->GetTileSize();
	int width = tileLayer->GetColumnCount() * tileSize;
	int height = tileLayer->GetRowCount() * tileSize;
	Camera::GetInstance()->SetSceneLimit(width, height);
}

void Collisor::Clean() {
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}


bool Collisor::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
	bool xOverlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool yOverlaps = (a.x < b.y + b.h) && (a.y + b.h > b.y);

	return (xOverlaps && yOverlaps);
}


bool Collisor::MapCollision(const SDL_Rect& rectToCheck) { 
	if (mCollisionLayer) {

		int tileSize = mCollisionLayer->GetTileSize(); 
		int rowCount = mCollisionLayer->GetRowCount(); //map height
		int colCount = mCollisionLayer->GetColumnCount(); //map width

		int leftTile = rectToCheck.x / tileSize;
		int rightTile = (rectToCheck.x + rectToCheck.w) / tileSize;

		int topTile = rectToCheck.y / tileSize;
		int bottomTile = (rectToCheck.y + rectToCheck.h) / tileSize;

		if (leftTile < 0) leftTile = 0;
		if (rightTile > colCount) rightTile = colCount;

		if (topTile < 0) topTile = 0;
		if (bottomTile > rowCount) bottomTile = rowCount;

		for (int i = leftTile; i <= rightTile; ++i) {
			for (int j = topTile; j <= bottomTile; ++j) {
				if (mCollisionTilemap[j][i] > 0) {
					return true;
				}
			}
		}

	}

	return false;
}

bool Collisor::PlaceFree(int x, int y, int w, int h) {
	SDL_Rect rectToVerify{};
	rectToVerify.x = x;
	rectToVerify.y = y;
	rectToVerify.w = w;
	rectToVerify.h = h;
	return !MapCollision(rectToVerify);
}