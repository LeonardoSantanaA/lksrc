#pragma once

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
	int firstID, lastID;
	int rowCount, columnCount;
	int tileCount, tileSize;
	std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer: public Layer {
public:
	TileLayer(int tileSize, int rowCount, int columnCount, TileMap tilemap, TilesetList tilesets);
	virtual void Update();
	virtual void Render();
	inline TileMap GetTilemap() { return mTilemap; }


private:
	int mTileSize;
	int mRowCount, mColumnCount;
	TileMap mTilemap;
	TilesetList mTilesets;


};