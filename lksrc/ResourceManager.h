#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <vector>

enum ImageFormat {
	FORMAT_BMP = 0,
	FORMAT_PNG,
	FORMAT_JPG,
};

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

class ResourceManager {
private:
	ResourceManager();
	ResourceManager(const ResourceManager& other);
	ResourceManager& operator=(const ResourceManager& other);
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_multimap<std::pair<std::string, int>, TTF_Font*, hash_pair> mFonts;
	//std::vector<StructFont> mFonts;

public:
	static ResourceManager& GetInstance();
	void ClearResourceManager();

	SDL_Surface* GetSurface(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);
	TTF_Font* GetFont(const std::string& filepath, int size);
};