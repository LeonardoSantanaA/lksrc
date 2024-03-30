#pragma once

#include "Vec2D.h"

class Transform {
public:
	float x, y;
	Transform(float x = 0, float y = 0): x(x), y(y) {}

	inline void Log(std::string msg = "") const {
		std::cout << msg << "(X, Y) = (" << x << ", " << y << ")" << std::endl;
	}

private:
	inline void TranslateX(float x) { this->x += x; }
	inline void TranslateY(float x) { this->x += x; }
	inline void Translate(Vec2D v) { x += v.x; y += v.y; }
};