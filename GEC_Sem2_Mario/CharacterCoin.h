#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
public:

	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterCoin();

	virtual void Update(float _deltaTime, SDL_Event e);
	virtual void Render();

private:

	float m_single_sprite_w, m_single_sprite_h;

	float m_frame_delay;

	int m_current_frame;
};

#endif _CHARACTERCOIN_H