#include <iostream>
#include <memory>
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


ResourceManager::ResourceManager() {
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		std::cerr << "failed to init sdl_image: " << IMG_GetError() << std::endl;
	}
	else {
		std::cout << "sdl_image initialized." << std::endl;
	}

	if (TTF_Init() == -1) {
		std::cerr << "failed to init sdl_ttf: " << TTF_GetError() << std::endl;
	}
	else {
		std::cout << "sdl_ttf initialized." << std::endl;
	}
}

ResourceManager::ResourceManager(const ResourceManager& other)
	:mSurfaces(other.mSurfaces), mFonts(other.mFonts)
{

}

ResourceManager& ResourceManager::operator=(const ResourceManager& other) {
	if (this != &other) {
		mSurfaces = other.mSurfaces;
		mFonts = other.mFonts;
	}
	return *this;
}

void ResourceManager::ClearResourceManager() {
	for (auto& pair: mSurfaces) {
		SDL_FreeSurface(pair.second);	
	}
	IMG_Quit();
	TTF_Quit();
}


ResourceManager& ResourceManager::GetInstance() {
	static ResourceManager sInstance;
	return sInstance;
}


SDL_Surface* ResourceManager::GetSurface(const std::string& filepath, const ImageFormat& format) {
	auto search = mSurfaces.find(filepath);
	if (search != mSurfaces.end()) {
		return mSurfaces[filepath];
	}
	else {
		switch (format) {
		case FORMAT_BMP: {
			SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
			if (surface == NULL) {
				std::cout << "couldn't load bmp surface: " << SDL_GetError() << std::endl;
			}
			else {
				std::cout << "new surface loaded: " << filepath.c_str() << std::endl;
			}
			mSurfaces.insert(std::make_pair(filepath, surface));
			break;
		}

		case FORMAT_PNG: {
			SDL_Surface* surface = IMG_Load(filepath.c_str());
			if (!surface) {
				std::cout << "couldn't load png surface: " << IMG_GetError() << std::endl;
			}
			else {
				std::cout << "new surface loaded: " << filepath.c_str() << std::endl;
			}
			mSurfaces.insert(std::make_pair(filepath, surface));
			break;
		}
		
		case FORMAT_JPG: {
			SDL_Surface* surface = IMG_Load(filepath.c_str());
			if (!surface) {
				std::cout << "couldn't load png surface: " << IMG_GetError() << std::endl;
			}
			else {
				std::cout << "new surface loaded: " << filepath.c_str() << std::endl;
			}
			mSurfaces.insert(std::make_pair(filepath, surface));
			break;
		}
		}	

		return mSurfaces[filepath];
		
	}

	return nullptr;
}

TTF_Font* ResourceManager::GetFont(const std::string& filepath, int size) {
	std::pair<std::string, int> pairToSearch = std::make_pair(filepath, size);
	auto search = mFonts.find(pairToSearch);
	if (search != mFonts.end()) {
		std::cout << "font found." << std::endl;
		return search->second;
	}
	else {
		std::cout << "new font opened." << std::endl;
		TTF_Font* newFont;
		newFont = TTF_OpenFont(filepath.c_str(), size);
		if (!newFont) {
			std::cerr << "cannot open the font: " << TTF_GetError() << std::endl;
			return nullptr;
		}
		mFonts.insert(std::make_pair(pairToSearch, newFont));
		return newFont;
	}
}


