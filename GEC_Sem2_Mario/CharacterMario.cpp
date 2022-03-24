#include "CharacterMario.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth()/ 12;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterMario::~CharacterMario() {

	
}

void CharacterMario::Render() {

	//single sprite render
	/*m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
		m_texture->Render(m_position, SDL_FLIP_NONE);
	else
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);*/

	//Mario Bros sprite sheet render
	//variable to hold the left position of the sprite we want to draw
	int _left = 0.0f;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { (m_single_sprite_w * m_current_frame),0,m_single_sprite_w, m_single_sprite_h };

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

void CharacterMario::Update(float deltaTime, SDL_Event e) {

	switch (e.type) {

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_a:

			m_moving_left = true;
			break;

		case SDLK_d:

			m_moving_right = true;
			break;

		case SDLK_w:

			if (m_can_jump)
				Jump();

			break;
		}

		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {

		case SDLK_a:

			m_moving_left = false;
			break;

		case SDLK_d:

			m_moving_right = false;
			break;

		case SDLK_w:

			m_jump_command = false;
			break;
		}

		break;
	}

	Character::Update(deltaTime, e);

	m_frame_delay -= deltaTime;

	if (m_frame_delay <= 0.0f) {

		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move frame over
		m_current_frame++;

		//loop frame around if it goes beyond number of frames
		if (m_current_frame > 2)
			m_current_frame = 0;
	}
}

void CharacterMario::SetPosition(Vector2D new_position) {


}

Vector2D CharacterMario::GetPosition() {

	return m_position;
}