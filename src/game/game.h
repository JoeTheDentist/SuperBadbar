/**
 * Classe jeu: gestion de la boucle de jeu
 * contient les Game, la caméra, le personnage
 * et gère le temps
 **/

#ifndef _JEU_
#define _JEU_
#include <stdint.h>
#include <iostream>



#define TIME_LOOP 50

class Dynamic_data;
class Talks;
class Static_data;
class Sound_manager;
class Camera;
class Dashboard;

class Game{
private:
	Keyboard m_keyboard;
	Sound_manager m_sound_manager;
	
	Static_data m_static_data;
	uint32_t m_time;					/* temps actuel */
	uint32_t m_previous_time;	/* temps depuis le dernier tour de jeu */
	Dynamic_data m_dynamic_data;
	Camera m_camera;				/* camera ciblant babar */
	Talks m_talks;
	Dashboard m_dashboard;		/* attention: pour le moment doit etre construit apres talks pour beneficier de SDL_TTF */
	void update_camera();       /* MàJ cam */
	void update_pos();			/* mise à jour des positions des sprites */
	void update_speed();		/* mise à jour des vitesses des sprites */
	void refresh_screen();		/* raffraichissement de l'écran */



public:
	Game();						/* constructeur */
	~Game();					/* destructeur */
	void game_loop();			/* boucle de jeu */
	void check_monsters();      /* Check collision monstres-projectiles */
	
};


#endif
