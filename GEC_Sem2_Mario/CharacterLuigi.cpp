#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth() / MARIOLUIGI_SPRITE_DIV_WIDTH; //28 good
	m_single_sprite_h = m_texture->GetHeight() / MARIOLUIGI_SPRITE_DIV_HEIGHT;  //32 good
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
	//variable to hold the left position of the sprite we want to draw
	int _left = 0.0f;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { LUIGI_SPRITE_POS_X, LUIGI_SPRITE_POS_Y, m_single_sprite_w, m_single_sprite_h };

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
			break;

		case SDLK_RIGHT:

			m_moving_right = true;
			break;

		case SDLK_UP:

			if (m_can_jump)
				Jump();

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
}

void CharacterLuigi::SetPosition(Vector2D new_position) {


}

Vector2D CharacterLuigi::GetPosition() {

	return m_position;
}