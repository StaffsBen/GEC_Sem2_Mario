#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetUpLevel();

	SetUpMusic();

	//m_level_map = nullptr; //idk i did this, im the stupid

	_newKoopaTimer = NEW_KOOPA_TIMER;
}

GameScreenLevel1::~GameScreenLevel1() {

	//std::cout << "GameScreenLevel1 deconstuct\n";

	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_musicplayer;
	m_musicplayer = nullptr;

	delete _charMario;
	_charMario = nullptr;

	delete _charLuigi;
	_charLuigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_coins.clear();

	m_enemies.clear();
}

void GameScreenLevel1::Update(float _deltaTime, SDL_Event e) {

	//SetLevelMap();
	
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
	_charMario->Update(_deltaTime, e);
	_charLuigi->Update(_deltaTime, e);

	if (Collisions::Instance()->Circle(_charMario, _charLuigi)) {

		std::cout << "Circle hit!\n";
	}

	if (Collisions::Instance()->Box(_charLuigi->GetCollisionBox(), _charMario->GetCollisionBox())) {

		std::cout << "Box hit!\n";
	}

	UpdatePowBlock();

	UpdateEnemies(_deltaTime, e);

	UpdateCoins(_deltaTime, e);

	//Spawns new Koopa's after 5 secs
	_newKoopaTimer = (_newKoopaTimer - _deltaTime);

	if (_newKoopaTimer <= 0.0f) {

		if (m_enemies.size() < MAX_KOOPA_NUM) {

			std::cout << "Koopa spawn!\n";

			//SetLevelMap();

			CreateKoopa(Vector2D(256, 32), FACING_RIGHT, KOOPA_SPEED);

			_newKoopaTimer = NEW_KOOPA_TIMER;
		}
	}
}

void GameScreenLevel1::Render() {

	//renders enemy chars
	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->Render();

	//renders coins
	for (int i = 0; i < m_coins.size(); i++)
		m_coins[i]->Render();
	
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//renders player characters
	_charMario->Render();
	_charLuigi->Render();

	//renders PowBlock
	m_pow_block->Render();
}

bool GameScreenLevel1::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl; 

		return false;
	}

	SetLevelMap();

	_charMario = new CharacterMario(m_renderer, "Images/SpriteSheetDoubledTransparent.png", Vector2D(64, 330), m_level_map); //"Images/SpriteSheetDoubledTransparent.png"
	_charLuigi = new CharacterLuigi(m_renderer, "Images/SpriteSheetDoubledTransparent.png", Vector2D(164, 330), m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoin(Vector2D(235, 350));
	CreateCoin(Vector2D(255, 350));

	m_screenshake = false;
	m_background_yPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap() {

	std::cout << "Levelmap made" << std::endl;

	/*int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },			original levelmap
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
	};*/

	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },		//modified levelmap, left platforms extended to match background
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1 },
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

void GameScreenLevel1::SetUpMusic() {

	m_musicplayer = new MusicPlayer();
	m_musicplayer->StopMusic();
	m_musicplayer->PlayMusic("Audio/Mario.mp3");
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
	else if (Collisions::Instance()->Box(_charLuigi->GetCollisionBox(), m_pow_block->GetCollisionBox())) {

		if (m_pow_block->IsAvailable()) {

			//collide while jumping
			if (_charLuigi->IsJumping()) {

				DoScreenShake();
				m_pow_block->TakeHit();
				_charLuigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake() {

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++) {

		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float _deltaTime, SDL_Event e) {

	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			//if (m_enemies[i]->GetPosition().y > 300.0f)
			//{
			//	//is the enemy off screen to the left / right?
			//	if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
			//		i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f)) {

			//		SetLevelMap();
			//		
			//		m_enemies[i]->SetAlive(false);

			//		std::cout << "Off screen!\n";
			//	}
			//		
			//}

			//now do the update
			m_enemies[i]->Update(_deltaTime, e);

			//Collides with edges of screen and reverses movement
			if (m_enemies[i]->GetPosition().x <= 2 || m_enemies[i]->GetPosition().x >= SCREEN_WIDTH - 30) {

				//SetLevelMap();
				
				m_enemies[i]->ChangeDirection();
			}

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) { 

				//ignore collisions if behind pipe
				//std::cout << "Behind Pipe!\n";
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], _charMario)) {

					if (m_enemies[i]->GetInjured()) {

						m_enemies[i]->SetAlive(false);
						std::cout << "Koopa dead!\n";
					}
					else {

						//kill mario
						//_charMario->SetAlive(false);
						std::cout << "Mario dead!\n";
					}
				}
				else if (Collisions::Instance()->Circle(m_enemies[i], _charLuigi)) {

					if (m_enemies[i]->GetInjured()) {

						m_enemies[i]->SetAlive(false);
						std::cout << "Koopa dead!\n";
					}
					else {

						//kill luigi
						//_charLuigi->SetAlive(false);
						std::cout << "Luigi dead!\n";
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {

	//std::cout << "Levelmap " << (m_level_map == nullptr) << std::endl;

	_charKoopa = new CharacterKoopa(m_renderer, "Images/SpriteSheetDoubledTransparentSpacingFixWIPbackup.png", position, direction, speed, m_level_map);

	m_enemies.push_back(_charKoopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position) {

	_charCoin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);

	m_coins.push_back(_charCoin);
}

void GameScreenLevel1::UpdateCoins(float _deltaTime, SDL_Event e) {

	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			//now do the update
			m_coins[i]->Update(_deltaTime, e);

			//check to see if enemy collides with player
			if (Collisions::Instance()->Circle(m_coins[i], _charMario)) {

				m_coins[i]->SetAlive(false);
				std::cout << "Coin collected!\n";
			}
			else if (Collisions::Instance()->Circle(m_coins[i], _charLuigi)) {

				m_coins[i]->SetAlive(false);
				std::cout << "Coin collected!\n";
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::DisplayText() {

	
}