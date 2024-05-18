#pragma once

#include <vector>
#include <SDL.h>
#include <memory>
#include "TileLayer.h"
#include "GameMap.h"

class Collisor {
public:
	inline static Collisor* GetInstance() {
		if (!mInstance) {
			mInstance = new Collisor;
		}
		return mInstance;
	}

	void SetCollisionLayer(TileLayer* tileLayer);

	void Clean();

	bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);

	//OBS: The last layer of Tiled is the collisor layer!
	//use the Collider2D(index)->GetColliderBoundingBox to check if collided.
	bool MapCollision(const SDL_Rect& a);

	bool PlaceFree(int x, int y, int w, int h);

private:
	Collisor();
	static Collisor* mInstance;
	TileMap mCollisionTilemap;
	TileLayer* mCollisionLayer;
};