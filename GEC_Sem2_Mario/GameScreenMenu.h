#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"


class Texture2D;

class GameScreenMenu : GameScreen
{

private:

	//background var
	Texture2D* m_background_texture;

	//level funcs and var
	bool SetUpLevel();

	float m_background_yPos;

public:

	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float _deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
};

#endif _GAMESCREENMENU_H