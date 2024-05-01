#pragma once

#include <vector>
#include "Layer.h"

class Map {
public:
	void Update();

	void Render();

	inline std::vector<Layer*> GetMapLayers() { return mMapLayers; }

private:
	friend class MapParser;
	std::vector<Layer*> mMapLayers;
};