#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>

using namespace std;

//Global vars
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//Functions prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

int main(int argc, char* args[]) {

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

		return true;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr) {

		//init PNG loading
		int _imageFlags = IMG_INIT_PNG;

		if (!(IMG_Init(_imageFlags)& _imageFlags)) {

			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
		else {

			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}

	//load the background texture
	g_texture = LoadTextureFromFile("Images/test.bmp");

	if (g_texture == nullptr) {

		return false;
	}
}

void CloseSDL() {

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//clear the texture
	FreeTexture();

	//release the renderer
	SDL_DestroyRenderer(g_renderer);

	g_renderer = nullptr;
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

void Render() {

	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//set where to render the texture
	SDL_Rect _renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &_renderLocation, 0, NULL, SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path) {

	//remove memory used for a previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());

	if (p_surface != nullptr) {

		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);

		if (p_texture == nullptr) {

			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}

		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else {

		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	//returns the texture
	return p_texture;
}

void FreeTexture() {

	//checks if texture exists before removing it
	if (g_texture != nullptr) {

		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}