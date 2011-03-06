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
	if (m_game)
		delete m_game;
	while(1) {
		m_game = new Game(m_level);
		switch(res = m_game->game_loop()) {
		case victory:
			m_level++;
			break;
		case defeat: case leave:
			return;
		default:
			break;
		}
	}
}
