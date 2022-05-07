#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenMenu.h"
#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {

	m_renderer = renderer;

	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {

	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render() {

	m_current_screen->Render();
}

void GameScreenManager::Update(float _deltaTime, SDL_Event e) {

	m_current_screen->Update(_deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) {

	//clear up old screen
	if (m_current_screen != nullptr) {

		delete m_current_screen;
	}

	GameScreenMenu* _tempScreenMenu;
	GameScreenLevel1* _tempScreenLv1;
	GameScreenLevel2* _tempScreenLv2;

	switch (new_screen) {

	case SCREEN_MENU:

		_tempScreenMenu = new GameScreenMenu(m_renderer);

		m_current_screen = (GameScreen*)_tempScreenMenu;

		_tempScreenMenu = nullptr;

		break;

	case SCREEN_LEVEL1:

		_tempScreenLv1 = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreenLv1;
		
		_tempScreenLv1 = nullptr;

		break;

	case SCREEN_LEVEL2:

		_tempScreenLv2 = new GameScreenLevel2(m_renderer);

		m_current_screen = (GameScreen*)_tempScreenLv2;

		_tempScreenLv2 = nullptr;

		break;

	default:

		break;
	}
}