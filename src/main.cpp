/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "util/debug.h"
#include "game/game.h"
#include "util/arg_analyser.h"
#include "menus/main_menu.h"
#include "game/game_initializer.h"

int main(int argc, char *argv[])
{
	PRINT_TRACE(1,"Lancement du jeu")
	Game_initializer::init_game();
	Arg_Analyser arg_analyser(argc, argv);
	if (arg_analyser.menu_on()) {
		Main_menu *menu = new Main_menu();
		delete menu;
	} else {
		Game *game = new Game(1, arg_analyser.record_on(), arg_analyser.replay_on(), arg_analyser.output_file(), arg_analyser.input_file());
		game->game_loop();
		delete game;
	}
	Game_initializer::close_game();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
