#include "CharacterFireball.h"
#include "LevelMap.h"

CharacterFireball::CharacterFireball(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_single_sprite_w = m_texture->GetWidth() / FIREBALL_SPRITE_DIV_WIDTH; //30
	m_single_sprite_h = m_texture->GetHeight() / FIREBALL_SPRITE_DIV_HEIGHT; //28

	//sets value of the drawn sprite modifier to 0, meaning it will draw the default sprite, in this case, the idle sprite
	_spriteXPosAdjust = 0;

	//sets values for animation delay
	_frameDelay = ANIMATION_DELAY;
	_frameChange = false;
}

CharacterFireball::~CharacterFireball() {


}

void CharacterFireball::Render() {

	if (_frameChange) {

		_spriteXPosAdjust += 30; //adds 30 to drawn sprite position, changing which sprite is drawn
		_frameDelay = ANIMATION_DELAY; //resets the frame delay
		_frameChange = false; //makes it so the frame cannot change until the delay reaches 0 again
	}


	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { (FIREBALL_SPRITE_POS_X + _spriteXPosAdjust), FIREBALL_SPRITE_POS_Y, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_NONE);
	}
}

void CharacterFireball::Update(float deltaTime, SDL_Event e) {

	//enemy is not injured so move
	if (m_facing_direction == FACING_LEFT) {

		m_position.x -= deltaTime * MOVEMENTSPEED;
	}
	else if (m_facing_direction == FACING_RIGHT) {

		m_position.x += deltaTime * MOVEMENTSPEED;
	}

	//if the sprite drawn position is larger than 128, the sprite is reset back to the idle sprite
	if (_spriteXPosAdjust > 113)
		_spriteXPosAdjust = 0;

	//frame delay countdown
	_frameDelay -= deltaTime;

	//if the frame delay value is equal to or less than 0, the frame is then allowed to change
	if (_frameDelay <= 0.0f) {

		_frameChange = true;
	}
}