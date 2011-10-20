/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Berard & Benoit Morel
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

#ifdef WIN32
    #undef main
#endif

#include <QApplication> //TEMP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        PRINT_TRACE(1,"Lancement du jeu");
        GameInitializer::init_game();
#ifdef ARG_ANALYSER_ON
        ArgAnalyser arg_analyser(argc, argv);
	if (arg_analyser.level_specified_on()) {
		Game *game = new Game(arg_analyser.get_level_name());
		game->game_loop();
		delete game;
	} else if(arg_analyser.menu_on()) {
                MainMenu *menu = new MainMenu();
		delete menu;
	} else {
		Game *game = new Game(Constants::TEST_LEVEL);
		game->game_loop();
                delete game;
	}
#else
	Main_menu *menu = new Main_menu();
	delete menu;	
#endif
	
        GameInitializer::close_game();
        PRINT_TRACE(1, "Fermeture du jeu");
        return 0;
}
