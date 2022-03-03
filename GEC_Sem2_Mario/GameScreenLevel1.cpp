#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetUpLevel();

	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_background_texture;
	m_background_texture = nullptr;

	//delete my_character;
	//my_character = nullptr;

	delete _charMario;
	_charMario = nullptr;

	delete _charLuigi;
	_charLuigi = nullptr;
}

void GameScreenLevel1::Update(float _deltaTime, SDL_Event e) {

	//update character
	//my_character->Update(_deltaTime, e);
	_charMario->Update(_deltaTime, e);
	_charLuigi->Update(_deltaTime, e);

	if (Collisions::Instance()->Circle(_charMario, _charLuigi)) {

		std::cout << "Circle hit!\n";
	}

	if (Collisions::Instance()->Box(_charLuigi->GetCollisionBox(), _charMario->GetCollisionBox())) {

		std::cout << "Box hit!\n";
	}
}

void GameScreenLevel1::Render() {

	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//renders character
	//my_character->Render();
	_charMario->Render();
	_charLuigi->Render();
}

bool GameScreenLevel1::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl; 

		return false;
	}

	//sets up player character
	//my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));

	SetLevelMap();

	_charMario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	_charLuigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(164, 330), m_level_map);

	return true;
}

void GameScreenLevel1::SetLevelMap() {

	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
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