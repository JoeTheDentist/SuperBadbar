#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "window.h"
#include "game.h"
#include "globals.h"


int main(int argc, char *argv[])
{
	open_window(window_weight, window_height);
	fill_screen(NULL);
	Game game;
	game.game_loop();
	close_window();

	return 0;
}
