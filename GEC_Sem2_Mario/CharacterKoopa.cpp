#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa() {

	
}

void CharacterKoopa::Render() {

	//variable to hold the left position of the sprite we want to draw
	int _left = 0.0f;

	//if injured move the left position to be the left position of the second image of the sprite sheet
	if (m_injured)
		_left = m_single_sprite_w;


	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { _left,0,m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_HORIZONTAL);
	}

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {

	//use the code within the base class
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		//enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		//we should not be moving when injured
		m_moving_right = false;
		m_moving_left = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();

	}

}

void CharacterKoopa::TakeDamage() {

	m_injured = true;

	m_injured_time = INJURED_TIME;

	Jump();
}

void CharacterKoopa::Jump() {

	if (!m_jumping) {

		m_jump_force = INITIAL_JUMP_FORCE;
		
		m_jumping = true;

		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightWayUp() {

	if (m_facing_direction == FACING_LEFT)
		m_facing_direction = FACING_RIGHT;
	else
		m_facing_direction = FACING_LEFT;
	
	m_injured = false;

	Jump();
}