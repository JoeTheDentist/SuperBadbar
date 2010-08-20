/**
 * Classe jeu: gestion de la boucle de jeu
 * contient les Game, la caméra, le personnage
 * et gère le temps
 **/

#ifndef _JEU_
#define _JEU_
#include <stdint.h>
#include "sprites.h"
#include "camera.h"

#define TIME_LOOP 50


class Game {
private:
	Babar m_babar;					/* sprite du personnage controlé par le joueur */
	Camera m_camera;				/* camera ciblant babar */
	uint32_t m_time;					/* temps actuel */
	uint32_t m_previous_time;	/* temps depuis le dernier tour de jeu */
	SDL_Surface *m_proj[4];     	/* images des projectiles dans tous les sens */

public:
	Game();							/* constructeur */
	~Game();							/* destructeur */
	void update_camera();       /* MàJ cam */
	void update_pos();			/* mise à jour des positions des sprites */
	void update_speed();		/* mise à jour des vitesses des sprites */
	void refresh_screen();		/* raffraichissement de l'écran */
	void game_loop();			/* boucle de jeu */
	SDL_Surface * proj(uint8_t i);   /* Accesseur : projectiles */
	SDL_Rect camera_frame();     /* Accesseur : cadre de la caméra */
};



#endif
