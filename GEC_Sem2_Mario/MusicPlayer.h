#pragma once
#ifndef _MUSICPLAYER_H
#define _MUSICPLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class MusicPlayer
{
private:

	Mix_Music* m_music;

public:

	MusicPlayer();
	~MusicPlayer();

	bool InitMixer();

	void LoadMusic(std::string path);

	void PlayMusic(std::string filepath);

	void StopMusic();
};

#endif _MUSICPLAYER_H