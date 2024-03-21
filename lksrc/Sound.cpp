#include <iostream>
#include <SDL.h>
#include "Sound.h"
#include "ResourceManager.h"

int Sound::mVolumeSound = 148;
int Sound::mVolumeMusic = 50;
std::vector<Mix_Chunk*> Sound::sounds;
std::vector<Mix_Music*> Sound::musics;


int Sound::LoadMusic(std::string filepath) {
	Mix_Music* m = nullptr;
	m = ResourceManager::GetInstance()->GetMusic(filepath);
	if (m == nullptr) {
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}

	musics.push_back(m);
	return musics.size() - 1;
}

int Sound::LoadSound(std::string filepath) {
	Mix_Chunk* s = nullptr;

	s = ResourceManager::GetInstance()->GetSound(filepath);

	if (s == nullptr) {
		std::cout << "Failed to load sound. Error: " << Mix_GetError() << std::endl;
	}

	sounds.push_back(s);
	return sounds.size() - 1;
}

void Sound::SetVolumeSound(int v) {
	mVolumeSound = (MIX_MAX_VOLUME * v) / 100;
}

void Sound::SetVolumeMusic(int v) {
	mVolumeMusic = (MIX_MAX_VOLUME * v) / 100;
}


int Sound::PlayMusic(int m) {
	if (Mix_PlayingMusic() == 0) {
		Mix_VolumeMusic(mVolumeMusic);
		Mix_PlayMusic(musics[m], -1);
	}

	return 0;
}

int Sound::PlaySound(int s) {
	Mix_Volume(-1, mVolumeSound);
	Mix_PlayChannel(-1, sounds[s], 0);

	return 0;
}


void Sound::QuitMixer() {
	sounds.clear();
	musics.clear();
	
}

void Sound::TogglePlay() {
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}