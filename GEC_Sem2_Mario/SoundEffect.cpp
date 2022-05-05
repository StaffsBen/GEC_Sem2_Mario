#include "SoundEffect.h"

SoundEffect::SoundEffect() {

	m_sfx = nullptr;

	InitMixer();
}

SoundEffect::~SoundEffect() {

	Mix_FreeChunk(m_sfx);

	m_sfx = nullptr;
}

bool SoundEffect::InitMixer() {

	//Initialse the audio mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

		std::cout << "Mixer could not init, Error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void SoundEffect::LoadSFX(std::string path) {

	m_sfx = Mix_LoadWAV(path.c_str());

	if (m_sfx == nullptr)
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
}

void SoundEffect::PlaySFX(std::string filepath) {

	//loads and loops music
	LoadSFX(filepath);

	std::cout << "SFX loaded!\n";

	Mix_PlayChannel(-1, m_sfx, 0);
}

void SoundEffect::StopSFX() {

	Mix_FreeChunk(m_sfx);
	m_sfx == nullptr;

	std::cout << "SFX unloaded!\n";
}