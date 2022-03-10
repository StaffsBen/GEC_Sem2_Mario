#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"

class Texture2D;

class Character;

class PowBlock;

class GameScreenLevel1 : GameScreen
{

private:

	//background var
	Texture2D* m_background_texture;

	//character vars
	Character* my_character;
	CharacterMario* _charMario;
	CharacterLuigi* _charLuigi;

	//level vars
	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* m_level_map;

	//powblock vars
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time, m_wobble, m_background_yPos;

	void DoScreenShake();

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float _deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
};

#endif _GAMESCREENLEVEL1_H