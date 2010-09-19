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
#include "dynamic_data.h"
#include "static_data.h"
#include "keyboard.h"
#define TIME_LOOP 50

class Dynamic_data;
class Static_data;

class Game {
private:
	Keyboard m_keyboard;
	Camera m_camera;				/* camera ciblant babar */
	Talks m_talks;

	Static_data m_static_data;
	uint32_t m_time;					/* temps actuel */
	uint32_t m_previous_time;	/* temps depuis le dernier tour de jeu */
	Dynamic_data m_dynamic_data;
	Babar m_babar;					/* sprite du personnage controlé par le joueur */


public:
	Game();							/* constructeur */
	~Game();							/* destructeur */
	void update_camera();       /* MàJ cam */
	void update_pos();			/* mise à jour des positions des sprites */
	void update_speed();		/* mise à jour des vitesses des sprites */
	void refresh_screen();		/* raffraichissement de l'écran */
	void game_loop();			/* boucle de jeu */
	void check_monsters();      /* Check collision monstres-projectiles */
	SDL_Rect camera_frame();     /* Accesseur : cadre de la caméra */
	
};


#endif
