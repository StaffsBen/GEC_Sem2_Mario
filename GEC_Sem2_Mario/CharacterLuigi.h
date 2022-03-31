#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"

class Texture2D;

class CharacterLuigi : public Character
{

public:

	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float m_single_sprite_w, m_single_sprite_h, _frameDelay;

	int m_current_frame, _spriteXPosAdjust;

	bool _frameChange;
};

#endif _CHARACTERLUIGI_H