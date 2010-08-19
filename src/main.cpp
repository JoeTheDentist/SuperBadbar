#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <time.h>

#include "sprites.h"
#include "window.h"
#include "game.h"
#include "globals.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));

	open_window(window_weight, window_height);
	fill_screen(NULL);
	game.game_loop();
	close_window();

	return 0;
}
