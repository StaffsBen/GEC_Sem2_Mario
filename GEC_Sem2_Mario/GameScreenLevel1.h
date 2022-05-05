#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterKoopaRed.h"
#include "CharacterCoin.h"
#include "CharacterText.h"
#include "LevelMap.h"
#include "MusicPlayer.h"
#include "SoundEffect.h"

class Texture2D;

class Character;

class PowBlock;

class GameScreenLevel1 : GameScreen
{

private:

	//texture vars
	Texture2D* m_background_texture;
	std::string _spriteSheet = "Images/SpriteSheetDoubledTransparentSpacingFixWIPbackup.png";

	//player character vars
	CharacterMario* _charMario;
	CharacterLuigi* _charLuigi;

	//enemy character vars and funcs
	void UpdateEnemies(float _deltaTime, SDL_Event e);
	void CreateKoopa(std::string texturePath, Vector2D position, FACING direction, float speed);
	std::vector<CharacterKoopa*> m_enemies;
	CharacterKoopa* _charKoopa;
	float _newKoopaTimer;

	CharacterKoopaRed* _charKoopaRed;

	//coin vars and funcs
	void CreateCoin(Vector2D position);
	CharacterCoin* _charCoin;
	std::vector<CharacterCoin*> m_coins;
	void UpdateCoins(float _deltaTime, SDL_Event e);

	//char vars
	void CreateText(Vector2D position, char symbol);
	CharacterText* _charText;
	std::vector <CharacterText*> m_textChars;
	void UpdateTextChars(float _deltaTime, SDL_Event e);
	int _scoreDigitsMario, _scoreTenthsMario, _scoreDigitsLuigi, _scoreTenthsLuigi;
	int _charDigitsMario, _charTenthsMario, _charDigitsLuigi, _charTenthsLuigi;

	//level funcs and var
	bool SetUpLevel();
	void SetLevelMap();
	void SetUpMusic();
	LevelMap* m_level_map;

	//powblock vars
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time, m_wobble, m_background_yPos;

	//screen shake func
	void DoScreenShake();

	//music player vars
	MusicPlayer* m_musicplayer;

	//SFX vars
	SoundEffect* m_sfx;

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float _deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
};

#endif _GAMESCREENLEVEL1_H