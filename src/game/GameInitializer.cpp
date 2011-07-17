#include "GameInitializer.h"
#include <time.h>
#include "../util/debug.h"
#include "../control/Keyboard.h"
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"
#include "../util/Constants.h"
//~ #include <fmodex/fmod.h>

#include "../util/globals.h"

bool GameInitializer::init_game()
{
	// chargement des librairies
	#ifdef WIN32
        freopen("CON", "w", stdout);
        freopen("CON", "r", stdin);
        freopen("CON", "w", stderr);
	#endif
	srand(time(NULL));
	Constants::init();
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
                PRINT_DEBUG(1, "Erreur d'initialisation de la SDL");
		return false;
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
		return false;
	}
	// chargement des variables globales Ã  l'ensemble du jeu
	gSound = new SoundEngine();
	gGraphics = new GraphicEngine();
	gGraphics->init_graphic_engine(false);
	gKeyboard = new Keyboard();
	return true;
}

bool GameInitializer::close_game()
{
	delete gSound;
	delete gGraphics;
	delete gKeyboard;
	PRINT_TRACE(1, "Fermeture de TTF")
	TTF_Quit();
	PRINT_TRACE(1, "Fermeture de SDL")
	SDL_Quit();
	return true;
}
