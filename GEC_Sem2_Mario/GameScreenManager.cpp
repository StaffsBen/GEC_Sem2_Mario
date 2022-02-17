#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

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

	GameScreenLevel1* _tempScreen;

	switch (new_screen) {

	case SCREEN_INTRO:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;

		_tempScreen = nullptr;

		break;

	case SCREEN_MENU:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;

		_tempScreen = nullptr;

		break;

	case SCREEN_LEVEL1:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;
		
		_tempScreen = nullptr;

		break;

	case SCREEN_LEVEL2:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;

		_tempScreen = nullptr;

		break;

	case SCREEN_GAMEOVER:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;

		_tempScreen = nullptr;

		break;

	case SCREEN_HIGHSCORES:

		_tempScreen = new GameScreenLevel1(m_renderer);

		m_current_screen = (GameScreen*)_tempScreen;

		_tempScreen = nullptr;

		break;

	default:

		break;
	}
}