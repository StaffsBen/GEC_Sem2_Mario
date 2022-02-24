#include <iostream>
#include "Texture2D.h"
#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	SetUpLevel();	
}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_character;
	my_character = nullptr;
}

void GameScreenLevel1::Update(float _deltaTime, SDL_Event e) {

	//update character
	my_character->Update(_deltaTime, e);
}

void GameScreenLevel1::Render() {

	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//renders character
	my_character->Render();
}

bool GameScreenLevel1::SetUpLevel() {

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/meme.png")) {

		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl; 

		return false;
	}

	//sets up player character
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));

	return true;
}