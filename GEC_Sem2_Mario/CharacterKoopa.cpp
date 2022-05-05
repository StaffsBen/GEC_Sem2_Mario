#include "CharacterKoopa.h"
#include "LevelMap.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / KOOPA_SPRITE_DIV_WIDTH;
	m_single_sprite_h = m_texture->GetHeight() / KOOPA_SPRITE_DIV_HEIGHT;

	//sets value of the drawn sprite modifier to 0, meaning it will draw the default sprite, in this case, the idle sprite
	_spriteXPosAdjust = 0;

	//sets values for animation delay
	_frameDelay = ANIMATION_DELAY;
	_frameChange = false;
}

CharacterKoopa::~CharacterKoopa() {

	
}

void CharacterKoopa::Render() {

	//if injured move the X position to the right, to where the first injured sprite is
	if (m_injured)
		_spriteXPosAdjust = KOOPA_INJURED_SPRITE_POS_ADJUST;

	if (_frameChange) {

		_spriteXPosAdjust += 32; //adds 32 to drawn sprite position, changing which sprite is drawn
		_frameDelay = ANIMATION_DELAY; //resets the frame delay
		_frameChange = false; //makes it so the frame cannot change until the delay reaches 0 again
	}


	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { (GREEN_KOOPA_SPRITE_POS_X + _spriteXPosAdjust), GREEN_KOOPA_SPRITE_POS_Y, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y + KOOPA_SPRITE_DRAW_ADJUST), m_single_sprite_w, m_single_sprite_h };

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

	if (!m_injured) {

		//enemy is not injured so move
		if (m_facing_direction == FACING_LEFT) {

			m_moving_left = true;
			m_moving_right = false;
			//m_position.x -= deltaTime * GREEN_KOOPA_SPEED;
		}
		else if (m_facing_direction == FACING_RIGHT) {

			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else {
		//we should not be moving when injured
		m_moving_right = false;
		m_moving_left = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();
	}

	//if the sprite drawn position is larger than 128, the sprite is reset back to the idle sprite
	if (_spriteXPosAdjust > 128)
		_spriteXPosAdjust = 0;

	//if the charater is jumping, the drawn sprite position has 180 added, moving to the jumping sprite
	if (m_jumping)
		_spriteXPosAdjust = 449;

	//frame delay countdown
	_frameDelay -= deltaTime;

	//if the frame delay value is equal to or less than 0, the frame is then allowed to change
	if (_frameDelay <= 0.0f) {

		//std::cout << "koopa frame change!\n";

		_frameChange = true;
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

	_spriteXPosAdjust = 0;

	Jump();
}

void CharacterKoopa::ChangeDirection() {

	if (m_facing_direction == FACING_LEFT) {

		m_facing_direction = FACING_RIGHT;
		m_moving_right = true;
		m_moving_left = false;
	}
	else if (m_facing_direction == FACING_RIGHT) {

		m_facing_direction = FACING_LEFT;
		m_moving_left = true;
		m_moving_right = false;
	}
}