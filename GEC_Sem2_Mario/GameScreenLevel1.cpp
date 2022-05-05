#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	srand(time(NULL));

	SetUpLevel();

	SetUpMusic();

	_newGreenKoopaTimer = NEW_KOOPA_TIMER;
	_newRedKoopaTimer = NEW_KOOPA_TIMER;
	_newKoopaTimerEnabled = true;

	_redKoopaJumpTimer = (rand() / RAND_MAX);
	_redKoopaJumpChance = false;

	_scoreTimer = SCORE_TIMER;

	_gameOverTextEnableStep1 = false;
	_gameOverTextEnableStep2 = true;
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

	m_greenKoopas.clear();

	m_redKoopas.clear();

	m_textChars.clear();
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
	_charMario->Update(_deltaTime, e);
	_charLuigi->Update(_deltaTime, e);

	if (Collisions::Instance()->Circle(_charMario, _charLuigi)) {

		std::cout << "Circle hit!\n";
	}

	if (Collisions::Instance()->Box(_charLuigi->GetCollisionBox(), _charMario->GetCollisionBox())) {

		std::cout << "Box hit!\n";

		//character collisions
		//if mario is facing right
		if (_charMario->m_facing_direction == FACING_RIGHT) {

			if (_charLuigi->m_facing_direction == FACING_LEFT) {

				_charMario->SetPosition(Vector2D(_charMario->GetPosition().x - 20.0f, _charMario->GetPosition().y)); //if facing opposite directions, both get bounced back by 20.0f
				_charLuigi->SetPosition(Vector2D(_charLuigi->GetPosition().x + 20.0f, _charLuigi->GetPosition().y)); //^
				m_sfx->PlaySFX("SFX/BumpSFX.wav");
			}
			else if (_charLuigi->m_facing_direction == FACING_RIGHT) {

				if (_charMario->GetPosition().x < _charLuigi->GetPosition().x) {

					_charLuigi->SetPosition(Vector2D(_charLuigi->GetPosition().x + 40.0f, _charLuigi->GetPosition().y)); //if mario runs into back of luigi, luigi bounced forward
					m_sfx->PlaySFX("SFX/BumpSFX.wav");
				}
				else if (_charMario->GetPosition().x > _charLuigi->GetPosition().x) {

					_charMario->SetPosition(Vector2D(_charMario->GetPosition().x + 40.0f, _charMario->GetPosition().y)); //if luigi runs into back of mario, mario bounced forward
					m_sfx->PlaySFX("SFX/BumpSFX.wav");
				}
			}
		}

		//if mario is facing left
		if (_charMario->m_facing_direction == FACING_LEFT) {

			if (_charLuigi->m_facing_direction == FACING_RIGHT) {

				_charMario->SetPosition(Vector2D(_charMario->GetPosition().x + 20.0f, _charMario->GetPosition().y)); //if facing opposite directions, both get bounced back by 20.0f
				_charLuigi->SetPosition(Vector2D(_charLuigi->GetPosition().x - 20.0f, _charLuigi->GetPosition().y)); //^
				m_sfx->PlaySFX("SFX/BumpSFX.wav");
			}
			else if (_charLuigi->m_facing_direction == FACING_LEFT) {

				if (_charMario->GetPosition().x < _charLuigi->GetPosition().x) {

					_charMario->SetPosition(Vector2D(_charMario->GetPosition().x - 40.0f, _charMario->GetPosition().y)); //if luigi runs into back of mario, mario bounced forward
					m_sfx->PlaySFX("SFX/BumpSFX.wav");
				}
				else if (_charMario->GetPosition().x > _charLuigi->GetPosition().x) {

					_charLuigi->SetPosition(Vector2D(_charLuigi->GetPosition().x - 40.0f, _charLuigi->GetPosition().y)); //if mario runs into back of luigi, luigi bounced forward
					m_sfx->PlaySFX("SFX/BumpSFX.wav");
				}
			}
		}
	}

	UpdatePowBlock();

	UpdateGreenKoopas(_deltaTime, e);

	UpdateRedKoopas(_deltaTime, e);

	UpdateCoins(_deltaTime, e);

	UpdateTextChars(_deltaTime, e);

	//if timer is enabled, it will count down from 5 secs
	if (_newKoopaTimerEnabled) {

		_newGreenKoopaTimer = (_newGreenKoopaTimer - _deltaTime);
		_newRedKoopaTimer = (_newRedKoopaTimer - _deltaTime);
	}

	//Spawns new green Koopa's after 5 secs, if the timer has been enabled, and if the number of green koopas is less than the max allowed
	if (_newGreenKoopaTimer <= 0.0f) {

		if (m_greenKoopas.size() < MAX_GREEN_KOOPA_NUM) {

			std::cout << "Koopa spawn!\n";

			CreateGreenKoopa(_spriteSheet, Vector2D(50, 25), FACING_RIGHT, GREEN_KOOPA_SPEED);

			_newGreenKoopaTimer = NEW_KOOPA_TIMER;

			m_sfx->PlaySFX("SFX/PipeSFX.wav");
		}
	}

	//Spawns new red Koopa's after 5 secs, if the timer has been enabled, and if the number of red is less than the max allowed
	if (_newRedKoopaTimer <= 0.0f) {

		if (m_redKoopas.size() < MAX_RED_KOOPA_NUM) {

			std::cout << "Koopa spawn!\n";

			CreateRedKoopa(_spriteSheet, Vector2D(460, 25), FACING_LEFT, RED_KOOPA_SPEED);

			_newRedKoopaTimer = NEW_KOOPA_TIMER;

			m_sfx->PlaySFX("SFX/PipeSFX.wav");
		}
	}

	//makes red koopa jump at a certain time
	_redKoopaJumpTimer = (_redKoopaJumpTimer - _deltaTime);

	if (_redKoopaJumpTimer <= 0.0f) {

		_redKoopaJumpTimer = RED_KOOPA_JUMP_TIMER;

		_redKoopaJumpChance = true;
	}

	//increments players score by 1 every few seeconds
	_scoreTimer = (_scoreTimer - _deltaTime);

	if (_scoreTimer <= 0.0f) {

		_scoreTimer = SCORE_TIMER;

		if (_charMario->GetAlive())
			_scoreDigitsMario++;
		
		if (_charLuigi->GetAlive())
			_scoreDigitsLuigi++;
	}

	//if both mario and luigi are dead, kill all koopas and stop new koopas spawning, also creates game over text
	if (!_charMario->GetAlive() && !_charLuigi->GetAlive()) {

		m_greenKoopas.clear();
		m_redKoopas.clear();
		_newKoopaTimerEnabled = false;

		//enables the first step of the game over text creation
		_gameOverTextEnableStep1 = true;

		if (_gameOverTextEnableStep1) {

			if (_gameOverTextEnableStep2) {

				CreateText(_spriteSheet, Vector2D(200, 200), 'g');
				CreateText(_spriteSheet, Vector2D(215, 200), 'a');
				CreateText(_spriteSheet, Vector2D(230, 200), 'm');
				CreateText(_spriteSheet, Vector2D(245, 200), 'e');

				CreateText(_spriteSheet, Vector2D(275, 200), 'o');
				CreateText(_spriteSheet, Vector2D(290, 200), 'v');
				CreateText(_spriteSheet, Vector2D(305, 200), 'e');
				CreateText(_spriteSheet, Vector2D(320, 200), 'r');

				//sets second step of game over text creation to be false, allowing code to only be run once, despite being in an update function
				_gameOverTextEnableStep2 = false;
			}
		}
	}
}

void GameScreenLevel1::Render() {

	//renders enemy chars
	for (int i = 0; i < m_greenKoopas.size(); i++)
		m_greenKoopas[i]->Render();

	for (int i = 0; i < m_redKoopas.size(); i++)
		m_redKoopas[i]->Render();

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

	//sets up level map
	SetLevelMap();

	//creates single instnaces of mario and luigi
	_charMario = new CharacterMario(m_renderer, _spriteSheet, Vector2D(70, 245), m_level_map);
	_charLuigi = new CharacterLuigi(m_renderer, _spriteSheet, Vector2D(410, 245), m_level_map);

	//create an instance of the PowBlock
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	//creates 2 instances of the green koopas, and 1 of the reed koopa
	CreateGreenKoopa(_spriteSheet, Vector2D(150, 32), FACING_RIGHT, GREEN_KOOPA_SPEED);
	CreateGreenKoopa(_spriteSheet, Vector2D(325, 32), FACING_LEFT, GREEN_KOOPA_SPEED);

	CreateRedKoopa(_spriteSheet, Vector2D(460, 25), FACING_LEFT, RED_KOOPA_SPEED);

	//creates 2 instances of the coin
	CreateCoin(Vector2D(235, 350));
	CreateCoin(Vector2D(255, 350));

	//creates the score text and counters, along with setting the vars for them
	CreateText(_spriteSheet, Vector2D(100, 20), 's');
	CreateText(_spriteSheet, Vector2D(115, 20), 'c');
	CreateText(_spriteSheet, Vector2D(130, 20), 'o');
	CreateText(_spriteSheet, Vector2D(150, 20), 'r');
	CreateText(_spriteSheet, Vector2D(165, 20), 'e');

	CreateText(_spriteSheet, Vector2D(310, 20), 's');
	CreateText(_spriteSheet, Vector2D(325, 20), 'c');
	CreateText(_spriteSheet, Vector2D(340, 20), 'o');
	CreateText(_spriteSheet, Vector2D(360, 20), 'r');
	CreateText(_spriteSheet, Vector2D(375, 20), 'e');

	_scoreDigitsMario = 0;
	_scoreTenthsMario = 0;

	_scoreDigitsLuigi = 0;
	_scoreTenthsLuigi = 0;

	CreateText(_spriteSheet, Vector2D(185, 20), _scoreTenthsMario);
	CreateText(_spriteSheet, Vector2D(200, 20), _scoreDigitsMario);

	CreateText(_spriteSheet, Vector2D(395, 20), _scoreTenthsLuigi);
	CreateText(_spriteSheet, Vector2D(410, 20), _scoreDigitsLuigi);

	//sets screenshake vars
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

void GameScreenLevel1::CreateGreenKoopa(std::string texturePath, Vector2D position, FACING direction, float speed) {

	_charKoopaGreen = new CharacterKoopa(m_renderer, texturePath, position, direction, speed, m_level_map); //"Images/SpriteSheetDoubledTransparentSpacingFixWIPbackup.png"

	m_greenKoopas.push_back(_charKoopaGreen);
}

void GameScreenLevel1::CreateRedKoopa(std::string texturePath, Vector2D position, FACING direction, float speed) {

	_charKoopaRed = new CharacterKoopaRed(m_renderer, texturePath, position, direction, speed, m_level_map); //"Images/SpriteSheetDoubledTransparentSpacingFixWIPbackup.png"

	m_redKoopas.push_back(_charKoopaRed);
}

void GameScreenLevel1::CreateCoin(Vector2D position) {

	_charCoin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);

	m_coins.push_back(_charCoin);
}

void GameScreenLevel1::CreateText(std::string texturePath, Vector2D position, char symbol) {

	//Creates text character and pushes to text char vector
	_charText = new CharacterText(m_renderer, texturePath, position, nullptr, symbol);

	m_textChars.push_back(_charText);
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

void GameScreenLevel1::UpdateGreenKoopas(float _deltaTime, SDL_Event e) {

	if (!m_greenKoopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_greenKoopas.size(); i++)
		{
			//now do the update
			m_greenKoopas[i]->Update(_deltaTime, e);

			//Collides with edges of screen and reverses movement
			if (m_greenKoopas[i]->GetPosition().x <= 2 || m_greenKoopas[i]->GetPosition().x >= SCREEN_WIDTH - 30) {

				//SetLevelMap();
				
				m_greenKoopas[i]->ChangeDirection();
			}

			//check to see if enemy collides with player
			if ((m_greenKoopas[i]->GetPosition().y <= 64.0f) && (m_greenKoopas[i]->
				GetPosition().x < 64.0f )) { 

				//ignore collisions if behind pipe
				//std::cout << "Behind Pipe!\n";
			}
			else if (m_greenKoopas[i]->GetPosition().y > 300.0f && m_greenKoopas[i]->GetPosition().x > SCREEN_WIDTH - 45.0f) {

				m_greenKoopas[i]->SetAlive(false);
				m_sfx->PlaySFX("SFX/PipeSFX.wav");
			}
			else
			{
				if (Collisions::Instance()->Circle(m_greenKoopas[i], _charMario)) {

					if (m_greenKoopas[i]->GetInjured()) {

						m_greenKoopas[i]->SetAlive(false);
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
						_charMario->DeathSFX();
					}
				}
				else if (Collisions::Instance()->Circle(m_greenKoopas[i], _charLuigi)) {

					if (m_greenKoopas[i]->GetInjured()) {

						m_greenKoopas[i]->SetAlive(false);
						std::cout << "Koopa dead!\n";
						_scoreDigitsLuigi++;
					}
					else {

						//kill luigi
						//_charLuigi->SetAlive(false);
						std::cout << "Luigi dead!\n";
						_charLuigi->SetAlive(false);
						_charLuigi->SetPosition(Vector2D(5000.0f, 6000.0f));
						_charLuigi->DeathSFX();
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_greenKoopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_greenKoopas.erase(m_greenKoopas.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateRedKoopas(float _deltaTime, SDL_Event e) {

	if (!m_redKoopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_redKoopas.size(); i++)
		{
			//now do the update
			m_redKoopas[i]->Update(_deltaTime, e);

			//Collides with edges of screen and reverses movement
			if (m_redKoopas[i]->GetPosition().x <= 2 || m_redKoopas[i]->GetPosition().x >= SCREEN_WIDTH - 30) {

				//SetLevelMap();

				m_redKoopas[i]->ChangeDirection();
			}

			//check to see if enemy collides with player
			if ((m_redKoopas[i]->GetPosition().y <= 64.0f) && (m_redKoopas[i]->
				GetPosition().x < 64.0f)) {

				//ignore collisions if behind pipe
				//std::cout << "Behind Pipe!\n";
			}
			else if (m_redKoopas[i]->GetPosition().y > 300.0f && m_redKoopas[i]->GetPosition().x < 40.0f) {

				m_redKoopas[i]->SetAlive(false);
				m_sfx->PlaySFX("SFX/PipeSFX.wav");
			}
			else
			{
				if (Collisions::Instance()->Circle(m_redKoopas[i], _charMario)) {

					//kill mario
					std::cout << "Mario dead!\n";
					_charMario->SetAlive(false);
					_charMario->SetPosition(Vector2D(5000.0f, 5000.0f));
					_charMario->DeathSFX();
				}
				else if (Collisions::Instance()->Circle(m_redKoopas[i], _charLuigi)) {

					//kill luigi
					std::cout << "Luigi dead!\n";
					_charLuigi->SetAlive(false);
					_charLuigi->SetPosition(Vector2D(5000.0f, 6000.0f));
					_charLuigi->DeathSFX();
				}
			}

			if (_redKoopaJumpChance) {

				m_redKoopas[i]->Jump();
				_redKoopaJumpChance = false;
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_redKoopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_redKoopas.erase(m_redKoopas.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateTextChars(float _deltaTime, SDL_Event e) {

	//system for player scoring system (pretty much just visual)

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
				m_sfx->PlaySFX("SFX/CoinSFX_2.wav");
			}
			else if (Collisions::Instance()->Circle(m_coins[i], _charLuigi)) {

				m_coins[i]->SetAlive(false);
				std::cout << "Coin collected!\n";
				_scoreDigitsLuigi++;
				m_sfx->PlaySFX("SFX/CoinSFX_2.wav");
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

void GameScreenLevel1::DoScreenShake() {

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_greenKoopas.size(); i++) {

		m_greenKoopas[i]->TakeDamage();
	}
}