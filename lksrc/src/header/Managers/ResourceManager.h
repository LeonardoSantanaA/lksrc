#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Managers/Utils.h"

enum ImageFormat {
	FORMAT_BMP = 0,
	FORMAT_PNG,
	FORMAT_JPG,
};

class ResourceManager {
public:
	static ResourceManager* GetInstance();
	void ClearResourceManager();

	std::shared_ptr<SDL_Surface> GetSurface(const std::string& filepath, const ImageFormat& format = FORMAT_BMP);
	TTF_Font* GetFont(const std::string& filepath, int size);
	Mix_Chunk* GetSound(const std::string& filepath);
	Mix_Music* GetMusic(const std::string& filepath);

private:
	ResourceManager();
	static ResourceManager* mInstance;
	ResourceManager(const ResourceManager& other);
	ResourceManager& operator=(const ResourceManager& other);
	std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> mSurfaces;
	std::unordered_multimap<std::pair<std::string, int>, TTF_Font*, hash_pair> mFonts;
	std::unordered_map<std::string, Mix_Chunk*> mSounds;
	std::unordered_map<std::string, Mix_Music*> mMusics;
};