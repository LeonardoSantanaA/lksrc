#pragma once

#include <SDL_mixer.h>
#include <vector>
#include <string>


class Sound {
public:
	static Sound* GetInstance();
	void ClearSound();

	int LoadMusic(std::string filepath);
	int LoadSound(std::string filepath);

	void SetVolumeSound(int v);
	void SetVolumeMusic(int v);

	inline int GetVolumeSound() const { return mVolumeSound; }
	inline int GetVolumeMusic() const { return mVolumeMusic; }

	int PlayMusic(int m);
	int PlaySound(int s);

	void QuitMixer();

	void TogglePlay();

private:
	Sound() :mVolumeMusic(60), mVolumeSound(30) {};
	static Sound* mInstance;

	int mVolumeSound;
	int mVolumeMusic;
	std::string mPath;

	std::vector<Mix_Chunk*> sounds;
	std::vector<Mix_Music*> musics;

};