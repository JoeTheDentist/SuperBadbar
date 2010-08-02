#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "window.h"
#include "globals.h"


uint8_t open_window(uint16_t weight, uint16_t height)
{

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
		return 0;
	}
	screen = SDL_SetVideoMode(weight, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
	SDL_WM_SetCaption("Babar Test", NULL);
	return 1;
}

uint8_t fill_screen(char *picture)
{
	SDL_Rect pos_screen = {0,0,0,0};
	if (picture == NULL){
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_BlitSurface(screen, NULL, screen, &pos_screen);
	} else {
		;
	}
	return 1;
}

void close_window()
{
	SDL_FreeSurface(screen);
	SDL_Quit();
}
