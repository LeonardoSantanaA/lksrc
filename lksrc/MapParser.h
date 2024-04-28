#pragma once

#include <map>
#include <string>
#include "thirdpart/TinyXML/tinyxml.h"
#include "Map.h"
#include "TileLayer.h"

class MapParser {
public:
	static MapParser* GetInstance();
	bool Load();
	void Clean();
	inline Map* GetMaps();
	

private:
	MapParser();
	static MapParser* mInstance;
	std::map<std::string, Map*> mMapDict;

	bool Parse(const std::string& id, const std::string& source);
	Tileset ParseTiteset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);
};