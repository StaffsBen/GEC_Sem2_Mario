#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
private:

	float m_single_sprite_w, m_single_sprite_h, m_injured_time, m_movement_speed, _frameDelay;

	int m_current_frame, _spriteXPosAdjust;

	bool m_injured, _frameChange;

	void FlipRightWayUp();

public:

	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map);
	~CharacterKoopa();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

	bool GetInjured() { return m_injured; }

	void ChangeDirection();
};

#endif _CHARACTERKOOPA_H