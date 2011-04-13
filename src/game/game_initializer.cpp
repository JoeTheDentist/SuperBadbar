#include "game_initializer.h"
#include <time.h>
#include "../util/debug.h"
#include "../control/keyboard.h"
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"
#include "../../lib/fmodapi375win/api/inc/fmod.h"

#include "../util/globals.h"

bool Game_initializer::init_game()
{
	// chargement des librairies
	#ifdef WIN32
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	freopen("CON", "w", stderr);
	#endif
	srand(time(NULL));
	PRINT_TRACE(1, "Initialisation de FMOD")
	FSOUND_Init(44100, 32, 0);
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
		return false;
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
		return false;
	}
	// chargement des variables globales à l'ensemble du jeu
	gSound = new Sound_engine();
	gGraphics = new Graphic_engine();
	gGraphics->init_graphic_engine(false);
	gKeyboard = new Keyboard();
	return true;
}

bool Game_initializer::close_game()
{
	delete gSound;
	delete gGraphics;
	PRINT_TRACE(1, "Fermeture de TTF")
	TTF_Quit();
	PRINT_TRACE(1, "Fermeture de SDL")
	SDL_Quit();
	PRINT_TRACE(1, "Fermeture de FMOD")
	FSOUND_Close();
	return true;
}
