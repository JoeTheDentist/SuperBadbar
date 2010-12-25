/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>
#include <time.h>

#include "util/debug.h"
#include "sprites/sprites.h"
#include "game/game.h"




int main(int argc, char *argv[])
{


	#ifdef WIN32
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);
	#endif

	PRINT_TRACE(1,"Lancement du jeu")
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
	}
	Game game;


    srand(time(NULL));

	game.game_loop();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
