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


int main(int argc, char *argv[])
{


	#ifdef WIN32
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	freopen("CON", "w", stderr);
	#endif

	Arg_Analyser arg_analyser(argc, argv);

	if (arg_analyser.arg_error()) {  //TODO
		PRINT_DEBUG(3, "Erreur lors de l'analyse des arguments");
		return 0;
	}

	PRINT_TRACE(1,"Lancement du jeu")

	Game game(arg_analyser.record_on(), arg_analyser.replay_on(), arg_analyser.output_file(), arg_analyser.input_file());


	srand(time(NULL));

	game.game_loop();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
