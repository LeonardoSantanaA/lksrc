#pragma once

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
	int firstID = 0, lastID = 0;
	int rowCount = 0, columnCount = 0;
	int tileCount = 0, tileSize = 0;
	std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer: public Layer {
public:
	TileLayer(int tileSize, int rowCount, int columnCount, TileMap tilemap, TilesetList tilesets);
	TileLayer(TileLayer&& other) noexcept;
	virtual void Update();
	virtual void Render();
	inline TileMap GetTilemap() { return mTilemap; }
	inline int GetTileSize() const { return mTileSize; }

	//returns height of TileLayer
	inline int GetRowCount() const { return mRowCount; }

	//returns width of TileLayer
	inline int GetColumnCount() const { return mColumnCount; }


private:
	int mTileSize;
	unsigned int mRowCount, mColumnCount;
	TileMap mTilemap;
	TilesetList mTilesets;


};