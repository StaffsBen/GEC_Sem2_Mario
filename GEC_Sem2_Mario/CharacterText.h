#pragma once
#ifndef _CHARACTERTEXT_H
#define _CHARACTERTEXT_H

#include "Character.h"

class Texture2D;

class CharacterText : public Character
{
private:

	char m_symbol;

	float m_single_sprite_w, m_single_sprite_h;

	int _spriteXPos, _spriteYPos;

public:

	CharacterText(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, char symbol);
	~CharacterText();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SymbolSelect(char symbol);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};

#endif _CHARACTERTEXT_H