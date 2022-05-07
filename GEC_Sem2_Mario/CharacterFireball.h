#pragma once
#ifndef _CHARACTERFIREBALL_H
#define _CHARACTERFIREBALL_H

#include "Character.h"

class LevelMap;

class CharacterFireball : public Character
{
private:

	float m_single_sprite_w, m_single_sprite_h, m_injured_time, m_movement_speed, _frameDelay;

	int m_current_frame, _spriteXPosAdjust;

	bool _frameChange;

	LevelMap* m_map;

public:

	CharacterFireball(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map);
	~CharacterFireball();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif _CHARACTERFIREBALL_H