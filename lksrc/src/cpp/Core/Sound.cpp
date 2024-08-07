#include <iostream>
#include <SDL.h>
#include "Core/Sound.h"
#include "Managers/ResourceManager.h"

Sound* Sound::mInstance = nullptr;

Sound* Sound::GetInstance() {
	if (!mInstance) {
		mInstance = new Sound;
	}

	return mInstance;
}

void Sound::ClearSound() {
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}

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
	Sound::GetInstance()->mVolumeSound = (MIX_MAX_VOLUME * v) / 100;
}

void Sound::SetVolumeMusic(int v) {
	Sound::GetInstance()->mVolumeMusic = (MIX_MAX_VOLUME * v) / 100;
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
	Sound::GetInstance()->sounds.clear();
	Sound::GetInstance()->musics.clear();
	
}

void Sound::TogglePlay() {
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}