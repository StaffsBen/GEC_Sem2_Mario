#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "GameScreenManager.h"

//from GameScreenMenu
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "PowBlock.h"

using namespace std;

//Global vars
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//Texture2D* g_texture = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;

//Functions prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[]) {

	if (InitSDL()) {

		//sets default screen to the Menu Screen
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);

		//set the time
		g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//game loop
		while (!quit) {

			Render();
			quit = Update();
		}
	}

	CloseSDL();
	
	return 0;
}

bool InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else {

		//setup passed, so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//did the window get created?
		if (g_window == nullptr) {

			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		//return true;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr) {

		//init PNG loading
		int _imageFlags = IMG_INIT_PNG;

		if (!(IMG_Init(_imageFlags) & _imageFlags)) {

			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else {

		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	return true;
}

void CloseSDL() {

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//destroy game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
}

bool Update() {

	Uint32 new_time = SDL_GetTicks();

	//event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type) {

		//click the X to quit
	case SDL_QUIT:

		return true;
		break;
	}

	switch (e.key.keysym.sym) {

	case SDLK_0:

		game_screen_manager->ChangeScreen(SCREEN_MENU);
		break;

	case SDLK_1:

		game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

	g_old_time = new_time;

	return false;
}

void Render() {

	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE, _imageAngle);
	game_screen_manager->Render();

	//updates the screen
	SDL_RenderPresent(g_renderer);
}

//from GameScreenMenu
//GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {
//
//	SetUpLevel();
//
//	SetUpMusic();
//}
//
//GameScreenMenu::~GameScreenMenu() {
//
//	delete m_background_texture;
//	m_background_texture = nullptr;
//
//	delete m_musicplayer;
//	m_musicplayer = nullptr;
//
//	delete _charMario;
//	_charMario = nullptr;
//
//	m_textChars.clear();
//}
//
//void GameScreenMenu::Update(float _deltaTime, SDL_Event e) {
//
//	_charMario->Update(_deltaTime, e);
//
//	if (_charMario->GetPosition().x < 140 && _charMario->GetPosition().y < 300) {
//
//		game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
//	}
//}
//
//void GameScreenMenu::Render() {
//
//	//draw the background
//	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
//
//	//draw mario
//	_charMario->Render();
//
//	//draw text
//	for (int i = 0; i < m_textChars.size(); i++)
//		m_textChars[i]->Render();
//}
//
//bool GameScreenMenu::SetUpLevel() {
//
//	//load texture
//	m_background_texture = new Texture2D(m_renderer);
//
//	if (!m_background_texture->LoadFromFile("Images/BackgroundMB_Lv2.png")) {
//
//		std::cout << "Failed to load background texture! Error: " << SDL_GetError() << std::endl;
//
//		return false;
//	}
//
//	SetLevelMap();
//
//	_charMario = new CharacterMario(m_renderer, _spriteSheet, Vector2D(240, 275), m_level_map);
//
//	CreateText(_spriteSheet, Vector2D(50, 300), 'l');
//	CreateText(_spriteSheet, Vector2D(65, 300), 'e');
//	CreateText(_spriteSheet, Vector2D(80, 300), 'v');
//	CreateText(_spriteSheet, Vector2D(95, 300), 'e');
//	CreateText(_spriteSheet, Vector2D(110, 300), 'l');
//	CreateText(_spriteSheet, Vector2D(140, 300), '1');
//
//	CreateText(_spriteSheet, Vector2D(350, 300), 'l');
//	CreateText(_spriteSheet, Vector2D(365, 300), 'e');
//	CreateText(_spriteSheet, Vector2D(380, 300), 'v');
//	CreateText(_spriteSheet, Vector2D(395, 300), 'e');
//	CreateText(_spriteSheet, Vector2D(410, 300), 'l');
//	CreateText(_spriteSheet, Vector2D(440, 300), '2');
//
//	m_background_yPos = 0.0f;
//
//	return true;
//}
//
//void GameScreenMenu::SetLevelMap() {
//
//	std::cout << "Levelmap made" << std::endl;
//
//	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },		//modified levelmap, left platforms extended to match background
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
//	};
//
//	//clear any old maps
//	if (m_level_map != nullptr)
//	{
//		delete m_level_map;
//	}
//
//	//set the new one
//	m_level_map = new LevelMap(map);
//}
//
//void GameScreenMenu::SetUpMusic() {
//
//	m_musicplayer = new MusicPlayer();
//	m_musicplayer->StopMusic();
//	m_musicplayer->PlayMusic("Audio/MarioTitle.mid");
//}
//
//void GameScreenMenu::CreateText(std::string texturePath, Vector2D position, char symbol) {
//
//	//Creates text character and pushes to text char vector
//	_charText = new CharacterText(m_renderer, texturePath, position, nullptr, symbol);
//
//	m_textChars.push_back(_charText);
//}