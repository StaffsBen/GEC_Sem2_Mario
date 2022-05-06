#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include <vector>
#include "Texture2D.h"
#include "MusicPlayer.h"
#include "LevelMap.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterText.h"

class Texture2D;

class Character;

class GameScreenMenu : GameScreen
{

private:

	//texture var
	Texture2D* m_background_texture;
	std::string _spriteSheet = "Images/SpriteSheetDoubledTransparentSpacingFixWIPv4.png";

	//level funcs and var
	bool SetUpLevel();
	LevelMap* m_level_map;
	void SetLevelMap();
	float m_background_yPos;
	void SetUpMusic();

	//GameScreenManager* _gSM;

	//mario vars
	CharacterMario* _charMario;

	//text char vars
	void CreateText(std::string texturePath, Vector2D position, char symbol);
	CharacterText* _charText;
	std::vector <CharacterText*> m_textChars;

	//music var
	MusicPlayer* m_musicplayer;

public:

	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float _deltaTime, SDL_Event e) override;

	
};

#endif _GAMESCREENMENU_H