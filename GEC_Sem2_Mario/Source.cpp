#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>

using namespace std;

//Global vars
SDL_Window* g_window = nullptr;

//Functions prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[]) {

	if (InitSDL()) {

		//flag to check if we wish to quit
		bool quit = false;

		//game loop
		while (!quit) {

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

		return true;
	}
}

void CloseSDL() {

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update() {

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

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {

		case SDLK_q:

			return true;
			break;
		}

	case SDL_MOUSEBUTTONDOWN:

		return true;
		break;
	}

	return false;
}