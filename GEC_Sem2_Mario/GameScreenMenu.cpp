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

	for (int i = 0; i < m_textChars.size(); i++) {

		delete m_textChars[i];
	}

	delete m_musicplayer;
	m_musicplayer = nullptr;
}

void GameScreenMenu::Update(float _deltaTime, SDL_Event e) {

	//system for player scoring system (pretty much just visual), could move to its own function
	
	//converts score vals to char vals for text characters
	_tempchar = '0' + _tempscore;
	_tc2 = '0' + _ts2;
	
	//changes 11th and 12th text chars to match current respective score vals
	m_textChars[10]->SymbolSelect(_tc2);
	m_textChars[11]->SymbolSelect(_tempchar);

	//if digit reaches 10, tenth is increased by one and digit is reset to 0. eg 09 -> 10, 19 -> 20
	if (_tempscore == 10) {

		//m_textChars[10]->SymbolSelect('0');
		_tempscore = 0;
		_ts2++;
	}

	//should keep whole score at 99 when 9 is reached for both, but doesnt rn
	if (_ts2 >= 9) {

		_ts2 = 9;

		if (_tempscore >= 9) {

			_ts2 = 9;
			_tempscore = 9;
		}
	}

	switch (e.type) {

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_o:

			_tempscore++;
			break;
		}
	}

	std::cout << "Score: " << _tempscore << std::endl;
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

	CreateText(Vector2D(50, 50), 's');
	CreateText(Vector2D(65, 50), 'c');
	CreateText(Vector2D(80, 50), 'o');
	CreateText(Vector2D(100, 50), 'r');
	CreateText(Vector2D(115, 50), 'e');

	CreateText(Vector2D(50, 100), 's');
	CreateText(Vector2D(65, 100), 'c');
	CreateText(Vector2D(80, 100), 'o');
	CreateText(Vector2D(100, 100), 'r');
	CreateText(Vector2D(115, 100), 'e');

	_tempscore = 0;
	_ts2 = 0;
	
	CreateText(Vector2D(130, 50), _tc2);
	CreateText(Vector2D(150, 50), _tempchar);
	CreateText(Vector2D(130, 100), _tempchar);

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