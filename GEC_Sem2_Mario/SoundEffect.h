#pragma once
#ifndef _SOUNDEFFECTS_H
#define _SOUNDEFFECTS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class SoundEffect
{
private:

	Mix_Chunk* m_sfx;

public:

	SoundEffect();
	~SoundEffect();

	bool InitMixer();

	void LoadSFX(std::string path);

	void PlaySFX(std::string filepath);

	void StopSFX();
};

#endif _SOUNDEFFECTS_H