/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010 (ca commence a dater)
 *
 */

#include <stdlib.h>

#include "util/debug.h"
#include "util/repertories.h"
#include "game/Game.h"
#include "util/ArgAnalyser.h"
#include "menus/MainMenu.h"
#include "game/GameInitializer.h"
#include "video/Talks.h"
#include "util/debug.h"
#include "util/globals.h"

int main(int argc, char *argv[])
{
	PRINT_TRACE(1,"Lancement du jeu")
	GameInitializer::init_game();

		Game *game = new Game(Constants::TEST_LEVEL);
		game->game_loop();
		delete game;


	GameInitializer::close_game();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
