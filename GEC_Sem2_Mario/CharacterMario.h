#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"

class Texture2D;

class CharacterMario : public Character
{

public:

	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterMario();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};

#endif _CHARACTERMARIO_H