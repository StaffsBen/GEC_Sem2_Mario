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

	delete m_sfx;
	m_sfx = nullptr;

	delete _charMario;
	_charMario = nullptr;

	delete _charLuigi;
	_charLuigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_coins.clear();

	m_enemies.clear();

	m_textChars.clear();
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

	UpdateTextChars(_deltaTime, e);

	//Spawns new Koopa's after 5 secs
	_newKoopaTimer = (_newKoopaTimer - _deltaTime);

	if (_newKoopaTimer <= 0.0f) {

		if (m_enemies.size() < MAX_KOOPA_NUM) {

			std::cout << "Koopa spawn!\n";

			//SetLevelMap();

			CreateKoopa(_spriteSheet, Vector2D(50, 25), FACING_RIGHT, GREEN_KOOPA_SPEED);

			_newKoopaTimer = NEW_KOOPA_TIMER;

			m_sfx->PlaySFX("SFX/PipeSFX.wav");
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

	//renders text chars
	for (int i = 0; i < m_textChars.size(); i++)
		m_textChars[i]->Render();
	
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//renders player characters
	if (_charMario->GetAlive())
		_charMario->Render();
	
	if (_charLuigi->GetAlive())
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

	_charMario = new CharacterMario(m_renderer, "Images/SpriteSheetDoubledTransparent.png", Vector2D(70, 280), m_level_map);
	_charLuigi = new CharacterLuigi(m_renderer, "Images/SpriteSheetDoubledTransparent.png", Vector2D(410, 280), m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(_spriteSheet, Vector2D(150, 32), FACING_RIGHT, GREEN_KOOPA_SPEED);
	CreateKoopa(_spriteSheet, Vector2D(325, 32), FACING_LEFT, GREEN_KOOPA_SPEED);

	CreateCoin(Vector2D(235, 350));
	CreateCoin(Vector2D(255, 350));

	CreateText(Vector2D(100, 20), 's');
	CreateText(Vector2D(115, 20), 'c');
	CreateText(Vector2D(130, 20), 'o');
	CreateText(Vector2D(150, 20), 'r');
	CreateText(Vector2D(165, 20), 'e');

	CreateText(Vector2D(310, 20), 's');
	CreateText(Vector2D(325, 20), 'c');
	CreateText(Vector2D(340, 20), 'o');
	CreateText(Vector2D(360, 20), 'r');
	CreateText(Vector2D(375, 20), 'e');

	_scoreDigitsMario = 0;
	_scoreTenthsMario = 0;

	_scoreDigitsLuigi = 0;
	_scoreTenthsLuigi = 0;

	CreateText(Vector2D(185, 20), _scoreTenthsMario);
	CreateText(Vector2D(200, 20), _scoreDigitsMario);

	CreateText(Vector2D(395, 20), _scoreTenthsLuigi);
	CreateText(Vector2D(410, 20), _scoreDigitsLuigi);

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

	m_sfx = new SoundEffect();
	m_sfx->StopSFX();
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
			if ((m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f )) { 

				//ignore collisions if behind pipe
				//std::cout << "Behind Pipe!\n";
			}
			else if (m_enemies[i]->GetPosition().y > 300.0f && m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 45.0f) {

				m_enemies[i]->SetAlive(false);
				m_sfx->PlaySFX("SFX/PipeSFX.wav");
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], _charMario)) {

					if (m_enemies[i]->GetInjured()) {

						m_enemies[i]->SetAlive(false);
						std::cout << "Koopa dead!\n";
						_scoreDigitsMario++;
						m_sfx->PlaySFX("SFX/EnemyDeathSFX.wav");
					}
					else {

						//kill mario
						//_charMario->SetAlive(false);
						std::cout << "Mario dead!\n";
						_charMario->SetAlive(false);
						_charMario->SetPosition(Vector2D(5000.0f, 5000.0f));
					}
				}
				else if (Collisions::Instance()->Circle(m_enemies[i], _charLuigi)) {

					if (m_enemies[i]->GetInjured()) {

						m_enemies[i]->SetAlive(false);
						std::cout << "Koopa dead!\n";
						_scoreDigitsLuigi++;
					}
					else {

						//kill luigi
						//_charLuigi->SetAlive(false);
						std::cout << "Luigi dead!\n";
						_charLuigi->SetAlive(false);
						_charLuigi->SetPosition(Vector2D(5000.0f, 6000.0f));
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

void GameScreenLevel1::CreateKoopa(std::string texturePath, Vector2D position, FACING direction, float speed) {

	//std::cout << "Levelmap " << (m_level_map == nullptr) << std::endl;

	_charKoopa = new CharacterKoopa(m_renderer, texturePath, position, direction, speed, m_level_map); //"Images/SpriteSheetDoubledTransparentSpacingFixWIPbackup.png"

	m_enemies.push_back(_charKoopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position) {

	_charCoin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);

	m_coins.push_back(_charCoin);
}

void GameScreenLevel1::CreateText(Vector2D position, char symbol) {

	//Creates text character and pushes to text char vector
	_charText = new CharacterText(m_renderer, "Images/SpriteSheetDoubledTransparentSpacingFixWIPv3.png", position, nullptr, symbol);

	m_textChars.push_back(_charText);
}

void GameScreenLevel1::UpdateTextChars(float _deltaTime, SDL_Event e) {

	//system for player scoring system (pretty much just visual), could move to its own function

	//text char vector vars
	int _marioTenths = 10, _marioDigits = 11, _luigiTenths = 12, _luigiDigits = 13;

	//converts score vals to char vals for text characters
	_charDigitsMario = '0' + _scoreDigitsMario;
	_charTenthsMario = '0' + _scoreTenthsMario;

	_charDigitsLuigi = '0' + _scoreDigitsLuigi;
	_charTenthsLuigi = '0' + _scoreTenthsLuigi;

	//changes 11th and 12th text chars to match current respective score vals
	m_textChars[_marioTenths]->SymbolSelect(_charTenthsMario);
	m_textChars[_marioDigits]->SymbolSelect(_charDigitsMario);

	m_textChars[_luigiTenths]->SymbolSelect(_charTenthsLuigi);
	m_textChars[_luigiDigits]->SymbolSelect(_charDigitsLuigi);

	//if digit reaches 10, tenth is increased by one and digit is reset to 0. eg 09 -> 10, 19 -> 20
	if (_scoreDigitsMario == 10) {

		//m_textChars[10]->SymbolSelect('0');
		_scoreDigitsMario = 0;
		_scoreTenthsMario++;
	}

	if (_scoreDigitsLuigi == 10) {

		_scoreDigitsLuigi = 0;
		_scoreTenthsLuigi++;
	}

	//should keep whole score at 99 when 9 is reached for both, but doesnt rn
	if (_scoreTenthsMario >= 9) {

		_scoreTenthsMario = 9;

		if (_scoreDigitsMario >= 9) {

			_scoreTenthsMario = 9;
			_scoreDigitsMario = 9;
		}
	}
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
				_scoreDigitsMario++;
				//m_sfx->PlaySFX("SFX/CoinSFX.mp3");
			}
			else if (Collisions::Instance()->Circle(m_coins[i], _charLuigi)) {

				m_coins[i]->SetAlive(false);
				std::cout << "Coin collected!\n";
				_scoreDigitsLuigi++;
				//m_sfx->PlaySFX("SFX/CoinSFX.mp3");
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