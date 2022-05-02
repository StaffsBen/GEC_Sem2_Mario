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

	for (int i = 0; i < m_textChars.size(); i++)
		m_textChars[i]->Render();
}

bool GameScreenMenu::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	/*if (!m_background_texture->LoadFromFile("Images/MenuPlaceholder1.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl;

		return false;
	}*/

	m_background_yPos = 0.0f;

	CreateText(Vector2D(50, 50), '0');
	CreateText(Vector2D(70, 50), '1');
	CreateText(Vector2D(90, 50), '2');
	CreateText(Vector2D(110, 50), '3');
	CreateText(Vector2D(130, 50), '4');
	CreateText(Vector2D(150, 50), '5');
	CreateText(Vector2D(170, 50), '6');
	CreateText(Vector2D(190, 50), '7');
	CreateText(Vector2D(210, 50), '8');
	CreateText(Vector2D(230, 50), '9');

	return true;
}

void GameScreenMenu::CreateText(Vector2D position, char symbol) {

	//Creates text character and pushes to text char vector
	_charText = new CharacterText(m_renderer, "Images/SpriteSheetDoubledTransparentSpacingFixWIPv3.png", position, nullptr, symbol);

	m_textChars.push_back(_charText);
}

void GameScreenMenu::SetUpMusic() {

	m_musicplayer = new MusicPlayer();
	m_musicplayer->StopMusic();
	m_musicplayer->PlayMusic("Audio/MarioUnderworld.mp3");
}