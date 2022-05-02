#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "GameScreen.h"
#include "Commons.h"
#include <vector>
#include "Texture2D.h"
#include "MusicPlayer.h"
#include "CharacterText.h"

class Texture2D;

class Character;

class GameScreenMenu : GameScreen
{

private:

	//background var
	Texture2D* m_background_texture;

	//level funcs and var
	bool SetUpLevel();
	float m_background_yPos;
	void SetUpMusic();

	//char vars
	void CreateText(Vector2D position, char symbol);
	CharacterText* _charText;
	std::vector <CharacterText*> m_textChars;

	//music var
	MusicPlayer* m_musicplayer;

	int _tempscore, _ts2; //temp, for testing, will remove
	char _tempchar, _tc2; //^

public:

	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float _deltaTime, SDL_Event e) override;

	
};

#endif _GAMESCREENMENU_H