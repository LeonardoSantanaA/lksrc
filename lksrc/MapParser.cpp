#include "MapParser.h"

MapParser* MapParser::GetInstance() {
	if (!mInstance) {
		mInstance = new MapParser();
	}
	return mInstance;
}

bool MapParser::Load() {
	return Parse("levelDemo", "assets/maps/mapDemo.tmx");
}

void MapParser::Clean() {

}

inline Map* MapParser::GetMaps() {

}

bool MapParser::Parse(const std::string& id, const std::string& source) {

}

Tileset MapParser::ParseTiteset(TiXmlElement* xmlTileset) {
	Tileset tileset;

	tileset.name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.firstID);
	xmlTileset->Attribute("tilecount", &tileset.tileCount);
	tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;
	xmlTileset->Attribute("columns", &tileset.columnCount);
	tileset.rowCount = tileset.tileCount / tileset.columnCount;
	xmlTileset->Attribute("tilewidth", &tileset.tileSize);
	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.source = image->Attribute("source");
	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount) {

}