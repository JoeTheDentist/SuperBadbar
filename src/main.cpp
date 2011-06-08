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
#include "util/arg_analyser.h"
#include "menus/main_menu.h"
#include "game/game_initializer.h"
#include "video/talks.h"

int main(int argc, char *argv[])
{
	PRINT_TRACE(1,"Lancement du jeu")
	Game_initializer::init_game();
	Arg_Analyser arg_analyser(argc, argv);
	if (arg_analyser.level_specified_on()) {
		Game *game = new Game(arg_analyser.get_level_name());
		game->game_loop();
		delete game;
		
	} else if(arg_analyser.menu_on()) {
		Main_menu *menu = new Main_menu();
		
		delete menu;
	} else {
		Game *game = new Game("test.lvl");
		game->game_loop();
		delete game;
	}
	Game_initializer::close_game();
	PRINT_TRACE(1, "Fermeture du jeu")
//~ 	Talks talks;
//~ 	talks.aux_cut_text("<plop> bla bla bla \n<plip> blibli bli");
	return 0;
}
