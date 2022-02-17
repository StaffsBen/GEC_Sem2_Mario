#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "GameScreenManager.h"

using namespace std;

//Global vars
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

//Functions prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[]) {

	game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);

	//set the time
	g_old_time = SDL_GetTicks();
	
	if (InitSDL()) {

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
			cout << "Window was not cerated. Error: " << SDL_GetError();
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

	//load the background texture
	/*g_texture = new Texture2D(g_renderer);

	if (!g_texture->LoadFromFile("Images/test.bmp")) {

		return false;
	}*/

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

	//release the texture
	/*delete g_texture;
	g_texture = nullptr;*/

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

	case SDL_MOUSEBUTTONDOWN:

		return true;
		break;
	}

	switch (e.key.keysym.sym) {
	
	case SDLK_q:

		return true;
		break;

	case SDLK_d:

		//_imageAngle = (_imageAngle + 1.0);
		break;

	case SDLK_a:

		//_imageAngle = (_imageAngle - 1.0);
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

	g_old_time = new_time;

	return false;
}

void Render() {

	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE, _imageAngle);
	game_screen_manager->Render();

	//updates the screen
	SDL_RenderPresent(g_renderer);
}