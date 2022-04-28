#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetUpLevel();

	SetUpMusic();
}

GameScreenMenu::~GameScreenMenu() {

	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_musicplayer;
	m_musicplayer = nullptr;
}

void GameScreenMenu::Update(float _deltaTime, SDL_Event e) {

	
}

void GameScreenMenu::Render() {

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

bool GameScreenMenu::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/MenuPlaceholder1.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl;

		return false;
	}

	m_background_yPos = 0.0f;

	return true;
}

void GameScreenMenu::SetUpMusic() {

	m_musicplayer = new MusicPlayer();
	m_musicplayer->StopMusic();
	m_musicplayer->PlayMusic("Audio/MarioUnderworld.mp3");
}