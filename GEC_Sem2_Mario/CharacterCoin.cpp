#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin() {


}

void CharacterCoin::Update(float _deltaTime, SDL_Event e) {

	//use the code within the base class
	Character::Update(_deltaTime, e);

	m_frame_delay -= _deltaTime;

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

void CharacterCoin::Render() {

	//get the portion of the sprite sheet you want to draw
	//							  {                  xPos,              yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { (m_single_sprite_w * m_current_frame),0,m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it
	m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_NONE);
}