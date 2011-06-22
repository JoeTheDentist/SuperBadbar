/**
 * 	@file level_manager.cpp
 * 	@brief implementation de la classe Levels_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "levels_manager.h"
#include "../game/game.h"
#include "../util/globals.h"
#include "../util/debug.h"
#include "../video/camera.h"
#include "../video/surface.h"
#include "../video/surface_text.h"
#include "../control/keyboard.h"
#include "../video/transition_screen.h"


Levels_manager::Levels_manager() :
	m_level(1),
	m_game(NULL)
{
	PRINT_CONSTR(1, "Creation du gestionnaire de niveaux")
}

Levels_manager::~Levels_manager()
{
	PRINT_CONSTR(1, "Destruction du gestionnaire de niveaux")
	if (m_game)
		delete m_game;
}

void Levels_manager::play()
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

void Levels_manager::play_defeat()
{
    Transition_screen * game_over = new Transition_screen("gameover.png", "GAMEOVER", "GAME OVER !!!");
	game_over->display(gGraphics->get_camera());

	game_over->wait_for_player();
	gSound->play_music();

	delete game_over;
}

void Levels_manager::the_end()
{
    Transition_screen * game_over = new Transition_screen("end.png", "END", "Le combat commence seulement !");
	game_over->display(gGraphics->get_camera());

	game_over->wait_for_player();
	gSound->play_music();

	delete game_over;
}
