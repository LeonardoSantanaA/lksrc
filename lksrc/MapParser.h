#pragma once

#include <map>
#include <string>
#include "thirdpart/TinyXML/tinyxml.h"
#include "GameMap.h"
#include "TileLayer.h"

class MapParser {
public:
	static MapParser* GetInstance();
	bool Load(const std::string& path);
	void Clean();
	std::shared_ptr<GameMap> GetMap(const std::string& id) const {
		auto it = mMapDict.find(id);
		if (it != mMapDict.end()) {
			return std::shared_ptr<GameMap>(it->second);
		}
		else {
			return nullptr; // ou lançar uma exceção, dependendo do comportamento desejado
		}
	}


private:
	//MapParser();
	static MapParser* mInstance;
	std::map<std::string, std::shared_ptr<GameMap>> mMapDict;

	bool Parse(const std::string& id, const std::string& source);
	Tileset ParseTiteset(TiXmlElement* xmlTileset);
	std::unique_ptr<TileLayer> ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);
};