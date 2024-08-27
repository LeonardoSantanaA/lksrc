#include <iostream>
#include "Map/TileLayer.h"
#include "Managers/TextureManager.h"
#include "Camera/Camera.h"

TileLayer::TileLayer(int tileSize, int rowCount, int columnCount, TileMap tilemap, TilesetList tilesets)
:mTileSize(tileSize), mRowCount(rowCount), mColumnCount(columnCount), mTilemap(tilemap), mTilesets(tilesets){

	for (unsigned int i = 0; i < mTilesets.size(); i++) {
		TextureManager::GetInstance()->Load(mTilesets[i].name, "assets/maps/" + mTilesets[i].source);
	}


}

TileLayer::TileLayer(TileLayer&& other) noexcept
	: mTileSize(other.mTileSize), mRowCount(other.mRowCount), mColumnCount(other.mColumnCount),
	mTilemap(std::move(other.mTilemap)), mTilesets(std::move(other.mTilesets))
{
	// move constructor
}

void TileLayer::Update() {

}

void TileLayer::Render() {
	for (unsigned int i = 0; i < mRowCount; i++) {
		for (unsigned int j = 0; j < mColumnCount; j++) {
			int tileID = mTilemap[i][j];

			if (tileID == 0) {
				continue;
			}
			else{
				int tsIndex = 0;
				if (mTilesets.size() > 1) {
					for (unsigned int k = 1; k < mTilesets.size(); k++) {
						if (tileID >= mTilesets[k].firstID && tileID <= mTilesets[k].lastID) {
							tileID = tileID + mTilesets[k].tileCount - mTilesets[k].lastID;
							tsIndex = k;
							break;
						}
					}
				}

				Tileset ts = mTilesets[tsIndex];
				int tileRow = tileID / ts.columnCount;
				int tileCol = tileID - tileRow * ts.columnCount - 1;
				

				//if this tile is on the last column
				if (tileID % ts.columnCount == 0) {
					tileRow--;
					tileCol = ts.columnCount - 1;
				}

				SDL_Rect tileRect = { j * ts.tileSize , i * ts.tileSize, ts.tileSize, ts.tileSize };

				auto camera = Camera::GetInstance();
				
				if (camera) {
					if (camera->IsInCamera(tileRect)) {
						TextureManager::GetInstance()->RenderTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
					}
				}
				else {
					TextureManager::GetInstance()->RenderTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
				}
				
				
			}

			

		}
	}
}
