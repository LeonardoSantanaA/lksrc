#pragma once

#include <string>

// A hash function used to hash a pair of any kind
struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const std::pair<T1, T2>& p) const
	{
		auto hash1 = std::hash<T1>{}(p.first);
		auto hash2 = std::hash<T2>{}(p.second);

		if (hash1 != hash2) {
			return hash1 ^ hash2;
		}

		// If hash1 == hash2, their XOR is zero.
		return hash1;
	}
};

static const float EPSILON = 0.0001f;

const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;
const float HALF_PI = 0.5f * PI;

bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);
float MillisecondsToSeconds(unsigned int milliseconds);

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c);

bool StringCompare(const std::string& a, const std::string& b);

float Clamp(float val, float min, float max);
int Sign(float val);

