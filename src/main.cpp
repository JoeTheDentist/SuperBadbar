/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include "util/debug.h"
#include "sprites/sprites.h"
#include "game/game.h"
#include "util/arg_analyser.h"

#include "AI/AI.h"

#ifdef WIN32
    #include "../lib/SDL/include/SDL/SDL.h"
    #include "../lib/SDL/include/SDL/SDL_ttf.h"

#else
    #include <SDL/SDL.h>
    #include <SDL/SDL_ttf.h>

#endif

void init_libraries()
{
	#ifdef WIN32
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	freopen("CON", "w", stderr);
	#endif
	srand(time(NULL));
	PRINT_TRACE(1, "Initialisation de FMOD")
	FSOUND_Init(44100, 32, 0);
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
	}
}

void close_libraries()
{

	PRINT_TRACE(1, "Fermeture de TTF")
	TTF_Quit();
	PRINT_TRACE(1, "Fermeture de SDL")
	SDL_Quit();
	PRINT_TRACE(1, "Fermeture de FMOD")
	FSOUND_Close();
}

int main(int argc, char *argv[])
{
	init_libraries();
	Arg_Analyser arg_analyser(argc, argv);
	if (arg_analyser.arg_error()) {  //TODO
		PRINT_DEBUG(3, "Erreur lors de l'analyse des arguments");
		return 0;
	}
	PRINT_TRACE(1,"Lancement du jeu")
	Game *game = new Game(arg_analyser.record_on(), arg_analyser.replay_on(), arg_analyser.output_file(), arg_analyser.input_file());
	game->game_loop();
	delete game;
	close_libraries();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
