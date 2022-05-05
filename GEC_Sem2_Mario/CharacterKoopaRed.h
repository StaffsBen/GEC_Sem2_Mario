#pragma once
#ifndef _CHARACTERKOOPARED_H
#define _CHARACTERKOOPARED_H

#include "CharacterKoopa.h"

class LevelMap;

class CharacterKoopaRed : public CharacterKoopa
{
public:

	CharacterKoopaRed(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map);
	~CharacterKoopaRed();
};

#endif _CHARACTERKOOPARED_H