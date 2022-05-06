#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	//_gSM = new GameScreenManager(renderer, SCREEN_LEVEL1);

	SetUpLevel();

	SetUpMusic();
}

GameScreenMenu::~GameScreenMenu() {

	delete m_background_texture;
	m_background_texture = nullptr;
	
	delete m_musicplayer;
	m_musicplayer = nullptr;

	delete _charMario;
	_charMario = nullptr;

	m_textChars.clear();
}

void GameScreenMenu::Update(float _deltaTime, SDL_Event e) {

	_charMario->Update(_deltaTime, e);

	/*switch (e.key.keysym.sym) {

	case SDLK_p:

		_gSM->ChangeScreen(SCREEN_LEVEL1);
		break;
	}*/
}

void GameScreenMenu::Render() {

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draw mario
	_charMario->Render();

	//draw text
	for (int i = 0; i < m_textChars.size(); i++)
		m_textChars[i]->Render();
}

bool GameScreenMenu::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB_Lv2.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl;

		return false;
	}

	SetLevelMap();

	_charMario = new CharacterMario(m_renderer, _spriteSheet, Vector2D(200, 200), m_level_map);

	CreateText(_spriteSheet, Vector2D(50, 300), 'l');
	CreateText(_spriteSheet, Vector2D(65, 300), 'e');
	CreateText(_spriteSheet, Vector2D(80, 300), 'v');
	CreateText(_spriteSheet, Vector2D(95, 300), 'e');
	CreateText(_spriteSheet, Vector2D(110, 300), 'l');
	CreateText(_spriteSheet, Vector2D(140, 300), '1');

	CreateText(_spriteSheet, Vector2D(350, 300), 'l');
	CreateText(_spriteSheet, Vector2D(365, 300), 'e');
	CreateText(_spriteSheet, Vector2D(380, 300), 'v');
	CreateText(_spriteSheet, Vector2D(395, 300), 'e');
	CreateText(_spriteSheet, Vector2D(410, 300), 'l');
	CreateText(_spriteSheet, Vector2D(440, 300), '2');

	CreateText(_spriteSheet, Vector2D(65, 340), '1');
	CreateText(_spriteSheet, Vector2D(90, 340), 'k');
	CreateText(_spriteSheet, Vector2D(105, 340), 'e');
	CreateText(_spriteSheet, Vector2D(120, 340), 'y');

	CreateText(_spriteSheet, Vector2D(365, 340), '2');
	CreateText(_spriteSheet, Vector2D(390, 340), 'k');
	CreateText(_spriteSheet, Vector2D(405, 340), 'e');
	CreateText(_spriteSheet, Vector2D(420, 340), 'y');

	m_background_yPos = 0.0f;

	

	return true;
}

void GameScreenMenu::SetLevelMap() {

	std::cout << "Levelmap made" << std::endl;

	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },		//modified levelmap, left platforms extended to match background
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenMenu::SetUpMusic() {

	m_musicplayer = new MusicPlayer();
	m_musicplayer->StopMusic();
	m_musicplayer->PlayMusic("Audio/MarioTitle.mid");
}

void GameScreenMenu::CreateText(std::string texturePath, Vector2D position, char symbol) {

	//Creates text character and pushes to text char vector
	_charText = new CharacterText(m_renderer, texturePath, position, nullptr, symbol);

	m_textChars.push_back(_charText);
}