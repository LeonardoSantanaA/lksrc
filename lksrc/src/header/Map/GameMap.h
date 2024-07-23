#pragma once

#include <vector>
#include <memory>
#include "Map/Layer.h"

class GameMap {
public:
	void Update();

	void Render();

	inline const std::vector<std::unique_ptr<Layer>>& GetMapLayers() const { return mMapLayers; }

private:
	friend class MapParser;
	std::vector<std::unique_ptr<Layer>> mMapLayers;
};