#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constants.h"
#include <string>
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundEffect.h"

class Texture2D;

class Character
{
private:

	LevelMap* m_current_level_map;

protected:

	

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	SoundEffect* m_sfx;

	bool m_moving_left;
	bool m_moving_right;

	bool m_jump_command;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	float m_collision_radius;

	bool m_alive;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	virtual void AddGravity(float deltaTime);
	virtual void Jump();

public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Circle2D GetCollisionRadiusAlt() { return Circle2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth() / COLLISIONBOX_WIDTH_ADJUST, m_texture->GetHeight() / COLLISIONBOX_HEIGHT_ADJUST); } //return Rect2D(m_position.x, m_position.y, m_texture->GetWidth() / 28, m_texture->GetHeight() / 32);

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }

	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }

	FACING m_facing_direction;
};

#endif _CHARACTER_H