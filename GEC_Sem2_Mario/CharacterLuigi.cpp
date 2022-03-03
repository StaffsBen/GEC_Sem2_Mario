#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {


}

CharacterLuigi::~CharacterLuigi() {


}

void CharacterLuigi::Render() {

	m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	else
		m_texture->Render(m_position, SDL_FLIP_NONE);
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