/**
 * Contient la boucle de jeu et les paramètres de la partie
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



Jeu::Jeu(): m_monstre(1, (SDL_Rect){100,100,30,30}, 50), m_camera(&m_babar)
{
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
	m_background = SDL_LoadBMP("../pic/background.bmp");
}
	
Jeu::~Jeu()
{
	SDL_FreeSurface(m_background);
}

void Jeu::update_pos()
{
	m_babar.update_pos();
	m_monstre.update_pos();
}

void Jeu::update_speed()
{
	m_babar.update_speed();
	m_monstre.update_speed();
}

void Jeu::refresh_screen()
{
	/* affichage du fond */
	m_camera.update_pos();
	SDL_Rect background_pos = m_camera.frame();
	background_pos.x = - background_pos.x; 
	background_pos.y = - background_pos.y;
	SDL_BlitSurface(m_background, NULL, screen, &background_pos); 
	/* affichage des sprites */
	m_camera.display_sprite(&m_babar);
	m_camera.display_sprite(&m_monstre);
	/* mise à jour */
	SDL_Flip(screen);
}

void Jeu::game_loop()
{
	bool end = false;
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			Events_stat.update_events();
			if (Events_stat.key_down(k_exit))
				end = true;
			update_speed();
			update_pos();
			refresh_screen();
			if (check_collision(m_babar.position(), m_monstre.position()))
				fprintf(stderr, "COLLISION\n");
			fprintf(stderr, "pourcentage d'utilisation du temps: %f\n", (float)(m_time - m_previous_time - TIME_LOOP)/100.0); // marge de temps
			m_previous_time = m_time;
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
}

