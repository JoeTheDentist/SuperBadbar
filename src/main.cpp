/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <stdlib.h>

#include "util/debug.h"
#include "util/repertories.h"
#include "game/game.h"
#include "util/ArgAnalyser.h"
#include "menus/MainMenu.h"
#include "game/GameInitializer.h"
#include "video/talks.h"
#include "util/debug.h"

int main(int argc, char *argv[])
{
	PRINT_TRACE(1,"Lancement du jeu")
	GameInitializer::init_game();
#ifdef ARG_ANALYSER_ON
	ArgAnalyser ArgAnalyser(argc, argv);
	if (ArgAnalyser.level_specified_on()) {
		Game *game = new Game(ArgAnalyser.get_level_name());
		game->game_loop();
		delete game;

	} else if(ArgAnalyser.menu_on()) {
		MainMenu *menu = new MainMenu();
		delete menu;
	} else {
		Game *game = new Game("test.lvl");
		game->game_loop();
		delete game;
	}
#else
	MainMenu *menu = new MainMenu();
	delete menu;
#endif

	GameInitializer::close_game();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
