#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth() / MARIOLUIGI_SPRITE_DIV_WIDTH; //28 good
	m_single_sprite_h = m_texture->GetHeight() / MARIOLUIGI_SPRITE_DIV_HEIGHT;  //32 good

	//sets value of the drawn sprite modifier to 0, meaning it will draw the default sprite, in this case, the idle sprite
	_spriteXPosAdjust = 0;

	//sets values for animation delay
	_frameDelay = ANIMATION_DELAY;
	_frameChange = false;
}

CharacterLuigi::~CharacterLuigi() {


}

void CharacterLuigi::Render() {

	//single sprite render
	/*m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	else
		m_texture->Render(m_position, SDL_FLIP_NONE);*/

	//sprite sheet render
	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { LUIGI_SPRITE_POS_X + _spriteXPosAdjust, LUIGI_SPRITE_POS_Y, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_LEFT) {

		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_NONE);
		//m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else {

		m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_HORIZONTAL);
		//m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {

	switch (e.type) {

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_LEFT:

			m_moving_left = true;

			//if the animation frame can change,
			if (_frameChange) {

				_spriteXPosAdjust += 32; //adds 32 to drawn sprite position, changing which sprite is drawn
				_frameDelay = ANIMATION_DELAY; //resets the frame delay
				_frameChange = false; //makes it so the frame cannot change until the delay reaches 0 again
			}

			break;

		case SDLK_RIGHT:

			m_moving_right = true;

			if (_frameChange) {

				_spriteXPosAdjust += 32;
				_frameDelay = ANIMATION_DELAY;
				_frameChange = false;
			}

			break;

		case SDLK_UP:

			if (m_can_jump) {

				Jump();
				m_sfx->PlaySFX("SFX/JumpSFX.wav");
			}

			break;
		}

		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {

		case SDLK_LEFT:

			m_moving_left = false;
			break;

		case SDLK_RIGHT:

			m_moving_right = false;
			break;

		case SDLK_UP:

			m_jump_command = false;
			break;
		}

		break;
	}

	Character::Update(deltaTime, e);

	//if the sprite drawn position is larger than 96, or 210, the sprite is reset back to the idle sprite
	if (_spriteXPosAdjust > 96 || _spriteXPosAdjust > 210)
		_spriteXPosAdjust = 0;

	//if the charater is jumping, the drawn sprite position has 180 added, moving to the jumping sprite
	if (m_jumping)
		_spriteXPosAdjust += 180;

	//frame delay countdown
	_frameDelay -= deltaTime;

	//if the frame delay value is equal to or less than 0, the frame is then allowed to change
	if (_frameDelay <= 0.0f) {

		_frameChange = true;
	}
}

void CharacterLuigi::SetPosition(Vector2D new_position) {

	m_position = new_position;
}

Vector2D CharacterLuigi::GetPosition() {

	return m_position;
}

void CharacterLuigi::DeathSFX() {

	m_sfx->PlaySFX("SFX/DeathSFX.wav");
}