#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include <SDL.h>
#include <iostream>
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"
#include "SoundEffect.h"

class LevelMap;

class PowBlock
{
public:

	PowBlock(SDL_Renderer* renderer, LevelMap* levelmap, Vector2D position);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth() / 3, m_texture->GetHeight()); }
	void TakeHit(int _levelNo);
	bool IsAvailable() { return m_num_hits_left > 0; }

private:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w, m_single_sprite_h;
	int m_num_hits_left;

	SoundEffect* m_sfx;
};

#endif _POWBLOCK_H