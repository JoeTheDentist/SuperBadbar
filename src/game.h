/**
 * Classe jeu: gestion de la boucle de jeu 
 * contient les monstres, la caméra, le personnage
 * et gère le temps
 **/

#ifndef _JEU_
#define _JEU_
#include <stdint.h>
#include "sprites.h"
#include "camera.h"

#define TIME_LOOP 50


class Jeu {
private:
	Babar m_babar;			/* sprite du personnage controlé par le joueur */
	Monstre m_monstre;		// temporaire
	Camera m_camera;		/* camera ciblant babar */
	uint32_t m_time;		/* temps actuel */
	uint32_t m_previous_time;	/* temps depuis le dernier tour de jeu */
	SDL_Surface *m_background;	/* image de fond */

public:
	Jeu();				/* constructeur */
	~Jeu();				/* destructeur */
	void update_pos();		/* mise à jour des positions des sprites */	
	void update_speed();		/* mise à jour des vitesses des sprites */	
	void refresh_screen();		/* raffraichissement de l'écran */
	void game_loop();		/* boucle de jeu */
};



#endif