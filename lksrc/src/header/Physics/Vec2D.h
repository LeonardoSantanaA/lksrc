#pragma once

#include <iostream>
#include <string>

class Vec2D {
public:
    static const Vec2D Zero;
	float x, y;

	Vec2D(float x = 0, float y = 0) : x(x), y(y) {};

    friend std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec);
    bool operator==(const Vec2D& vec) const;
    bool operator!=(const Vec2D& vec) const;

    Vec2D operator+(const Vec2D& other) const;
    Vec2D operator-(const Vec2D& other) const;
    Vec2D operator-() const;
    Vec2D operator*(float scale) const;
    Vec2D operator/(float scale) const;
    Vec2D& operator*=(float scale);
    Vec2D& operator/=(float scale);
    Vec2D& operator+=(const Vec2D& vec);
    Vec2D& operator-=(const Vec2D& vec);

    float Mag2() const;
    float Mag() const;

    Vec2D GetUnitVec() const;
    Vec2D& Normalize();

    float Distance(const Vec2D vec) const;
    float Dot(const Vec2D& vec) const;

    Vec2D ProjectOnto(const Vec2D& vec2) const;

    float AngleBetween(const Vec2D& vec2) const;

    Vec2D Reflect(const Vec2D& normal) const;

    void Rotate(float angle, const Vec2D& aroundPoint);
    Vec2D RotationResult(float angle, const Vec2D& aroundPoint) const;

    friend Vec2D operator*(float scale, const Vec2D& vec);

    inline void Log(std::string msg = "") const {
        std::cout << msg << "(X, Y) = (" << x << ", " << y << ")" << std::endl;
    }

};