#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "window.h"
#include "debug.h"
#include "globals.h"


uint32_t open_window(uint16_t weight, uint16_t height)
{

	PRINT_TRACE(1, "Initialisation de la SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
		return 0;
	}
	if (full_screen) {
		PRINT_TRACE(1, "Ouverture de la fenetre en mode full_screen")
		screen = SDL_SetVideoMode(weight, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	}
	else {
		PRINT_TRACE(1, "Ouverture de la fenetre (de taille %d*%d)", weight, height)
		screen = SDL_SetVideoMode(weight, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
	}
	SDL_WM_SetCaption("SuperBabar", NULL);
	return 1;
}

uint32_t fill_screen(char *picture)
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
	PRINT_TRACE(1, "Fermeture de la fenetre")
	PRINT_TRACE(1, "Fermeture de la SDL")

	SDL_FreeSurface(screen);
	SDL_Quit();
}
