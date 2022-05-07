#include "CharacterText.h"
#include "Texture2D.h"

CharacterText::CharacterText(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, char symbol) : Character(renderer, imagePath, start_position, map) {

	m_single_sprite_w = m_texture->GetWidth() / TEXT_SPRITE_DIV_WIDTH;
	m_single_sprite_h = (m_texture->GetHeight() / TEXT_SPRITE_DIV_HEIGHT);

	//sets default x and y sprite positions on the sprite sheet
	_spriteXPos = 25;
	_spriteYPos = 348;

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

	//changes x position of the drawn portion of the sprite sheet, in order to draw specified character
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

		_spriteXPos = 166;
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

	case 'i':

		_spriteXPos = 330;
		break;

	case 'j':

		_spriteXPos = 343;
		break;

	case 'k':

		_spriteXPos = 356;
		break;

	case 'l':

		_spriteXPos = 368;
		break;

	case 'm':

		_spriteXPos = 383;
		break;

	case 'n':

		_spriteXPos = 400;
		break;

	case 'o':

		_spriteXPos = 415;
		break;

	case 'p':

		_spriteXPos = 432;
		break;

	case 'q':

		_spriteXPos = 447;
		break;

	case 'r':

		_spriteXPos = 464;
		break;

	case 's':

		_spriteXPos = 478;
		break;

	case 't':

		_spriteXPos = 492;
		break;

	case 'u':

		_spriteXPos = 506;
		break;

	case 'v':

		_spriteXPos = 520;
		break;

	case 'w':

		_spriteXPos = 534;
		break;

	case 'x':

		_spriteXPos = 550;
		break;

	case 'y':

		_spriteXPos = 564;
		break;

	case 'z':

		_spriteXPos = 577;
		break;
	}
}

void CharacterText::SetPosition(Vector2D new_position) {


}

Vector2D CharacterText::GetPosition() {

	return m_position;
}