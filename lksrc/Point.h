#pragma once

class Point {
public: 
	float x, y;

	Point(float x = 0, float y = 0) : x(x), y(x) {};

	inline Point operator+(const Point& p2) const {
		return Point(x + p2.x, y + p2.y);
	}

	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.x += p2.x;
		p1.y += p2.y;
		return p1;
	}

	inline Point operator-(const Point& p2) const {
		return Point(x - p2.x, y - p2.y);
	}

	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.x -= p2.x;
		p1.y -= p2.y;
		return p1;
	}

	inline Point operator*(const float scalar) const {
		return Point(x * scalar, y * scalar);
	}

};