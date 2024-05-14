#pragma once

#include <vector>
#include <string>
#include "SDL_mixer.h"

class Sound {
public:
	static Sound* GetInstance();
	void ClearSound();

	int LoadMusic(std::string filepath);
	int LoadSound(std::string filepath);

	static void SetVolumeSound(int v);
	static void SetVolumeMusic(int v);

	int PlayMusic(int m);
	int PlaySound(int s);

	static void QuitMixer();

	void TogglePlay();

private:
	Sound() :mVolumeMusic(20), mVolumeSound(30) {};
	static Sound* mInstance;

	int mVolumeSound;
	int mVolumeMusic;
	std::string mPath;

	std::vector<Mix_Chunk*> sounds;
	std::vector<Mix_Music*> musics;

};