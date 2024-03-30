#pragma once

#include <iostream>
#include <string>

class Vec2D {
public:
	float x, y;
	Vec2D(float x = 0, float y = 0) : x(x), y(y) {};

	inline Vec2D operator+(const Vec2D& other) const {
		return Vec2D(x + other.x, y + other.y);
	}

	inline Vec2D operator-(const Vec2D& other) const {
		return Vec2D(x - other.x, y - other.y);
	}

	inline void Log(std::string msg = "") const {
		std::cout << msg << "(X, Y) = (" << x << ", " << y << ")" << std::endl;
	}

private:


};