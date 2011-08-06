

#include "GameInitializer.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <time.h>

#include "control/Keyboard.h"
#include <control/KeyboardConfig.h>
#include "util/globals.h"
#include "util/utils.h"

bool GameInitializer::init_game()
{
	// chargement des librairies
	srand(time(NULL));
	Constants::init();
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
                PRINT_DEBUG(1, "SDL initialization failed");
		return false;
	}
	SDL_EnableUNICODE( 1 );
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "TTF SDL initialization failed");
		return false;
	}
	// chargement des variables globales a  l'ensemble du jeu
	gSound = new SoundEngine();
	gGraphics = new GraphicEngine();
	gGraphics->init_graphic_engine(false);
	gKeyboard = new Keyboard();
	gKeyboardConfig = new KeyboardConfig();
	return true;
}

bool GameInitializer::close_game()
{
	delete gSound;
	delete gGraphics;
	delete gKeyboard;
	delete gKeyboardConfig;
	PRINT_TRACE(1, "Closing de TTF")
	TTF_Quit();
	PRINT_TRACE(1, "Closing de SDL")
	SDL_Quit();
	return true;
}
