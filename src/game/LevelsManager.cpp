/**
 * 	@file level_manager.cpp
 * 	@brief implementation de la classe LevelsManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "LevelsManager.h"
#include "../game/game.h"
#include "../util/globals.h"
#include "../util/debug.h"
#include "../video/Camera.h"
#include "../video/surface.h"
#include "../video/SurfaceText.h"
#include "../control/Keyboard.h"
#include "../video/TransitionScreen.h"


LevelsManager::LevelsManager() :
	m_level(1),
	m_game(NULL)
{
	PRINT_CONSTR(1, "Creation du gestionnaire de niveaux")
}

LevelsManager::~LevelsManager()
{
	PRINT_CONSTR(1, "Destruction du gestionnaire de niveaux")
	if (m_game)
		delete m_game;
}

void LevelsManager::play()
{
	result_game res;
	while(m_level != 6) {
		delete m_game;
		m_game = NULL;
		m_game = new Game(m_level);
		switch(res = m_game->game_loop()) {
		case victory:
			m_level++;
			break;
		case defeat:
			play_defeat();
			return;
		case leave:
			delete m_game;
			m_game = NULL;
			return;
		default:
			break;
		}
	}
	the_end();
}

void LevelsManager::play_defeat()
{
    TransitionScreen * game_over = new TransitionScreen("gameover.png", "GAMEOVER", "GAME OVER !!!");
	game_over->display(gGraphics->get_camera());

	game_over->wait_for_player();
	gSound->play_music();

	delete game_over;
}

void LevelsManager::the_end()
{
    TransitionScreen * game_over = new TransitionScreen("end.png", "END", "Le combat commence seulement !");
	game_over->display(gGraphics->get_camera());

	game_over->wait_for_player();
	gSound->play_music();

	delete game_over;
}
