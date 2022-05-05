#pragma once
#ifndef _CHARACTERKOOPARED_H
#define _CHARACTERKOOPARED_H

#include "Character.h"

class LevelMap;

class CharacterKoopaRed : public Character
{
private:

	float m_single_sprite_w, m_single_sprite_h, m_injured_time, m_movement_speed, _frameDelay;

	int m_current_frame, _spriteXPosAdjust;

	bool m_injured, _frameChange;

	void FlipRightWayUp();

	LevelMap* m_map;

public:

	CharacterKoopaRed(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map);
	~CharacterKoopaRed();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

	bool GetInjured() { return m_injured; }

	void ChangeDirection();
};

#endif _CHARACTERKOOPARED_H