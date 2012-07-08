
#include "GameInitializer.h"

#include <time.h>

#include "control/Keyboard.h"
#include "control/KeyboardConfig.h"
#include "util/globals.h"
#include "util/utils.h"

bool GameInitializer::init_game()
{
	// chargement des librairies
	srand(time(NULL));
	Constants::init();
	
	// chargement des variables globales a  l'ensemble du jeu
	gPlayers = new PlayersManager();
	gSound = new SoundEngine();
	gGraphics = new GraphicEngine();
	gGraphics->init_graphic_engine(false);
	gKeyboardConfig = new KeyboardConfig();
	return true;
}

bool GameInitializer::close_game()
{
	delete gSound;
	delete gGraphics;
	Keyboard::Destroy();
	delete gKeyboardConfig;
	return true;
}
