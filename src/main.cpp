/**
 * 	@file main.cpp
 * 	@brief main du jeu
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

//~ #include <SFML/Graphics.hpp>
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
//~ 	sf::RenderWindow my_window;

	Game game;


    srand(time(NULL));

	game.game_loop();
	PRINT_TRACE(1, "Fermeture du jeu")
	return 0;
}
