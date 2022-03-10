#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

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

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Update(float _deltaTime, SDL_Event e) {

	//does screen shake if required
	if (m_screenshake) {

		m_shake_time -= _deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//ends shake after duration
		if (m_shake_time <= 0.0f) {

			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	
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

	UpdatePowBlock();
}

void GameScreenLevel1::Render() {

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//renders character
	//my_character->Render();
	_charMario->Render();
	_charLuigi->Render();

	m_pow_block->Render();
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

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

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
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
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

void GameScreenLevel1::UpdatePowBlock() {

	if (Collisions::Instance()->Box(_charMario->GetCollisionBox(), m_pow_block->GetCollisionBox())) {

		if (m_pow_block->IsAvailable()) {

			//collide while jumping
			if (_charMario->IsJumping()) {

				DoScreenShake();
				m_pow_block->TakeHit();
				_charMario->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake() {

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}