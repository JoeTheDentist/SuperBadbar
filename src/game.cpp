/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible à partir de la touche "jouer" du menu
**/


#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "game.h"
#include "sprites.h"
#include "window.h"
#include "globals.h"
#include "events.h"
#include "camera.h"
#include "collisions.h"
#include "levels.h"
#include "statics.h"


Game::Game(): m_camera(&m_babar)
{
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();

	/*** Images des projectiles ***/
    m_proj[0] = SDL_LoadBMP("../pic/projectiles/left-right.bmp");
    m_proj[1] = SDL_LoadBMP("../pic/projectiles/up-down.bmp");
    m_proj[2] = SDL_LoadBMP("../pic/projectiles/top-left.bmp");
    m_proj[3] = SDL_LoadBMP("../pic/projectiles/top-right.bmp");

    for(int i = 0;i<4;i++) {
        SDL_SetColorKey(m_proj[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_proj[i]->format, 0, 0, 255));
    }
}

Game::~Game()
{
    for(int i = 0;i<4;i++) {
        SDL_FreeSurface(m_proj[i]);
    }
}

void Game::update_pos()
{
	m_babar.update_pos();
	/*m_monster.update_pos();*/
	while(!projectiles.end()) {
	    projectiles.element()->update_pos();
	    projectiles.next();
	}
	projectiles.init();

	while(!monsters.end()) {
	    monsters.element()->update_pos();
	    monsters.next();
	}
	monsters.init();
}

void Game::update_speed()
{
	m_babar.update_speed();

    while(!monsters.end()) {
	    monsters.element()->update_speed();
	    monsters.next();
	}
	monsters.init();

	m_babar.update_state();         /* A changer de place, en discuter */
}

void Game::update_camera()
{
    m_camera.update_pos();
}

void Game::refresh_screen()
{
	/* affichage du fond */
	m_camera.update_pos();
	SDL_Rect background_pos = m_camera.frame();
	background_pos.x = - background_pos.x;
	background_pos.y = - background_pos.y;
	SDL_BlitSurface(curr_lvl.background(), NULL, screen, &background_pos);

	/* affichage des statics (à faire en premier car derrière -> p-e pas tous...) */
	while(!statics.end()) {
	    m_camera.display_static(statics.element());
	    statics.next();
	}
	statics.init();

    /* affichage des monstres */
	while(!monsters.end()) {
	    m_camera.display_sprite(monsters.element());
	    monsters.next();
	}
	monsters.init();

	/* affichage des projectiles */
	while(!projectiles.end()) {
	    m_camera.display_sprite(projectiles.element());
	    projectiles.next();
	}
	/* suppression de projectiles trop vieux */
    projectiles.delete_elements(too_old);

	/* affichage des sprites */
	m_camera.display_sprite(&m_babar);

	/* mise à jour */
	SDL_Flip(screen);
}

void Game::game_loop()
{
	bool end = false;
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			Events_stat.update_events();
			if (Events_stat.key_down(k_exit))
				end = true;
            curr_lvl.update();
			update_speed();
			update_pos();
			refresh_screen();
			fprintf(stderr, "pourcentage d'utilisation du temps: %f\n", (float)(m_time - m_previous_time - TIME_LOOP)/100.0); // marge de temps
			m_previous_time = m_time;
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
}

SDL_Surface * Game::proj(uint8_t i)
{
    return m_proj[i];
}

SDL_Rect Game::camera_frame()
{
    return m_camera.frame();
}

