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
	#ifdef WIN32
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);
	#endif

	if (argc > 1)
		full_screen = true;

    srand(time(NULL));

	open_window(window_weight, window_height);
	fill_screen(NULL);
	game.game_loop();
	close_window();

	return 0;
}
