#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Managers/ResourceManager.h"


ResourceManager* ResourceManager::mInstance = nullptr;

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
	
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mixer couldn't init. Error: " << Mix_GetError() << std::endl;
	}
	std::cout << "sdl_mixer started." << std::endl;
	
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
	for (auto& pair : mSounds) {
		if (pair.second) {
			Mix_FreeChunk(pair.second);
		}
	}
	mSounds.clear();

	for (auto& pair : mMusics) {
		if (pair.second) {
			Mix_FreeMusic(pair.second);
		}
	}
	mMusics.clear();


	for (auto& pair : mFonts) {
		if (pair.second) {
			TTF_CloseFont(pair.second);
		}
	}

	mSurfaces.clear();

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();

	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}



ResourceManager* ResourceManager::GetInstance() {
	if (!mInstance) {
		mInstance = new ResourceManager();
	}
	return mInstance;
}

//deleter for sdl_surface
auto SDLSurfaceDeleter = [](SDL_Surface* surface) {
	if (surface) {
		std::cout << "surface destroyed!!" << std::endl;
		SDL_FreeSurface(surface);
	}
	};

std::shared_ptr<SDL_Surface> ResourceManager::GetSurface(const std::string& filepath, const ImageFormat& format) {
	auto search = mSurfaces.find(filepath);
	if (search != mSurfaces.end()) { //surface found
		return search->second;
	}
	else {
		std::shared_ptr<SDL_Surface> surface;
		switch (format) {
		case FORMAT_BMP: {
			SDL_Surface* rawSurface = SDL_LoadBMP(filepath.c_str());
			if (!rawSurface) {
				std::cout << "couldn't load bmp surface: " << SDL_GetError() << std::endl;
				return nullptr;
			}
			surface.reset(rawSurface, SDLSurfaceDeleter);
			std::cout << "new surface loaded: " << filepath << std::endl;
			break;
		}

		case FORMAT_PNG:
		case FORMAT_JPG: {
			SDL_Surface* rawSurface = IMG_Load(filepath.c_str());
			if (!rawSurface) {
				std::cout << "couldn't load image surface: " << IMG_GetError() << std::endl;
				return nullptr;
			}
			surface.reset(rawSurface, SDLSurfaceDeleter);
			std::cout << "new surface loaded: " << filepath << std::endl;
			break;
		}

		default:
			std::cout << "unsupported image format" << std::endl;
			return nullptr;
		}

		if (surface) {
			mSurfaces[filepath] = surface;
			return surface;
		}
	}
	return nullptr;
}

TTF_Font* ResourceManager::GetFont(const std::string& filepath, int size) {
	std::pair<std::string, int> pairToSearch = std::make_pair(filepath, size);
	auto search = mFonts.find(pairToSearch);
	if (search != mFonts.end()) {
		SDL_Log("font found.");
		return search->second;
	}
	else {
		std::cout << "new font opened:" << filepath << std::endl;
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

Mix_Chunk* ResourceManager::GetSound(const std::string& filepath) {
	auto search = mSounds.find(filepath);
	if (search != mSounds.end()) {
		return mSounds[filepath];
	}
	else {
		std::cout << "new sound loaded." << std::endl;
		Mix_Chunk* newSound;
		newSound = Mix_LoadWAV(filepath.c_str());
		mSounds.insert(std::make_pair(filepath, newSound));
		return mSounds[filepath];
	}
	return nullptr;
}

Mix_Music* ResourceManager::GetMusic(const std::string& filepath) {
	auto search = mMusics.find(filepath);
	if (search != mMusics.end()) {
		return mMusics[filepath];
	}
	else {
		std::cout << "new music loaded." << std::endl;
		Mix_Music* newMusic;
		newMusic = Mix_LoadMUS(filepath.c_str());
		mMusics.insert(std::make_pair(filepath, newMusic));
		return mMusics[filepath];
	}
	return nullptr;
}

