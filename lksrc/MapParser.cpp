#include "MapParser.h"

std::unique_ptr<MapParser> MapParser::mInstance = nullptr;

MapParser* MapParser::GetInstance() {
	if (!mInstance) {
		mInstance = std::make_unique<MapParser>();
		std::cout << "mapparser instance created." << std::endl;
	}
	return mInstance.get();
}

//dont need to write format file.
bool MapParser::Load(const std::string& path) {
	return Parse("mapDemo", "assets/maps/" + path+ ".tmx");
}

void MapParser::Clean() {
	mMapDict.clear();
}

bool MapParser::Parse(const std::string& id, const std::string& source) {

	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cerr << "failed to load xml map: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();

	//parse sizes
	int rowCount = 0, colCount = 0, tileSize = 0;
	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	//parse tilesets
	TilesetList tileset;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tileset.push_back(ParseTiteset(e));
		}
	}

	//parse layers
	std::unique_ptr<GameMap> gameMap = std::make_unique<GameMap>(GameMap());
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			std::unique_ptr<TileLayer> tileLayer = ParseTileLayer(e, tileset, tileSize, rowCount, colCount);
			gameMap->mMapLayers.push_back(std::move(tileLayer));
			
		}
	}

	mMapDict[id] = std::move(gameMap);
	return true;
	
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

std::unique_ptr<TileLayer> MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount) {
	TiXmlElement* data{};
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			data = e;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowCount, std::vector<int>(colCount, 0));
	
	for (int row = 0; row < rowCount; row++) {
		for (int col = 0; col < colCount; col++) {
			std::getline(iss, id, ',');
			std::istringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good()) {
				break;
			}
		}
	}

	return std::make_unique<TileLayer>(TileLayer(tileSize, rowCount, colCount, tilemap, tilesets));

}