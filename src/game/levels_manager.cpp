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
	while(1) {
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
}

void Levels_manager::play_defeat()
{
	Camera *camera = gGraphics->get_camera();
	Surface *game_over_surface = new Surface(PIC_TRANSITIONS_R + "gameover.png");
	Rect game_over_pos;
	game_over_pos.x = 0;
	game_over_pos.y = 0;
	camera->display_picture(game_over_surface, &game_over_pos, true);
	Surface_text *text = new Surface_text("GAME OVER", 70, 0, 0, 0);
	game_over_pos.x = 300;
	game_over_pos.y = 200;
	camera->display_picture(text, &game_over_pos, true);
	camera->flip_camera();
	gKeyboard->wait_key(k_fire);
	delete game_over_surface;
	delete text;
}
