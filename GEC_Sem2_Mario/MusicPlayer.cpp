#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {

	m_music = nullptr;

	InitMixer();
}

MusicPlayer::~MusicPlayer() {

	Mix_FreeMusic(m_music);
	m_music == nullptr;
}

bool MusicPlayer::InitMixer() {

	//Initialse the audio mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

		std::cout << "Mixer could not init, Error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void MusicPlayer::LoadMusic(std::string path) {

	m_music = Mix_LoadMUS(path.c_str());

	if (m_music == nullptr)
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
}

void MusicPlayer::PlayMusic(std::string filepath) {

	//loads and loops music
	LoadMusic(filepath);

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(m_music, -1);
}

void MusicPlayer::StopMusic() {

	Mix_HaltMusic();

	Mix_FreeMusic(m_music);
	m_music == nullptr;
}