#include "CharacterText.h"
#include "Texture2D.h"

CharacterText::CharacterText(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, char symbol) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth() / TEXT_SPRITE_DIV_WIDTH; //28 good
	m_single_sprite_h = m_texture->GetHeight() / TEXT_SPRITE_DIV_HEIGHT;  //32 good

	//sets value of the drawn sprite modifier to 0, meaning it will draw the default sprite, in this case, the idle sprite
	_spriteXPos = 25;
	_spriteYPos = 349;

	SymbolSelect(symbol);
}

CharacterText::~CharacterText() {


}

void CharacterText::Render() {

	//Mario Bros sprite sheet render
	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect _portion_of_sprite = { _spriteXPos, _spriteYPos, m_single_sprite_w, m_single_sprite_h }; //25 349 for 0

	//determine where you want it drawn
	SDL_Rect _destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(_portion_of_sprite, _destRect, SDL_FLIP_NONE);
}

void CharacterText::Update(float deltaTime, SDL_Event e) {


}

void CharacterText::SymbolSelect(char symbol) {

	switch (symbol) {

	case '0':

		_spriteXPos = 25;
		break;

	case '1':

		_spriteXPos = 42;
		break;

	case '2':

		_spriteXPos = 59;
		break;

	case '3':

		_spriteXPos = 77;
		break;

	case '4':

		_spriteXPos = 95;
		break;

	case '5':

		_spriteXPos = 113;
		break;

	case '6':

		_spriteXPos = 131;
		break;

	case '7':

		_spriteXPos = 149;
		break;

	case '8':

		_spriteXPos = 167;
		break;

	case '9':

		_spriteXPos = 185;
		break;

	case 'a':

		_spriteXPos = 222;
		break;

	case 'b':

		_spriteXPos = 236;
		break;

	case 'c':

		_spriteXPos = 250;
		break;

	case 'd':

		_spriteXPos = 264;
		break;

	case 'e':

		_spriteXPos = 276;
		break;

	case 'f':

		_spriteXPos = 288;
		break;

	case 'g':

		_spriteXPos = 303;
		break;

	case 'h':

		_spriteXPos = 318;
		break;
	}
}

void CharacterText::SetPosition(Vector2D new_position) {


}

Vector2D CharacterText::GetPosition() {

	return m_position;
}