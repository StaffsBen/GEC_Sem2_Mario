#include <SDL.h>
#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) {

	m_renderer = renderer;
}

GameScreen::~GameScreen() {

	m_renderer = nullptr;
}

void GameScreen::Render() {


}
	
void GameScreen::Update(float _deltaTime, SDL_Event e) {


}