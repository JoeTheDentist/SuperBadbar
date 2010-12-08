/**
 * Classe jeu: gestion de la boucle de jeu
 * contient les Game, la caméra, le personnage
 * et gère le temps
 **/

#ifndef _JEU_
#define _JEU_
#include <stdint.h>
#include <iostream>

#include "../sound/sound.h"


#define TIME_LOOP 50

class Game_engine;
class Talks;
class Static_data;
class Sound_manager;
class Camera;
class Dashboard;
class Keyboard;
class Events_manager;


class Game {
private:
	Sound_manager *m_sound_manager;
	Keyboard *m_keyboard;
	Static_data *m_static_data;
	Game_engine *m_game_engine;
	Camera *m_camera;				
	Talks *m_talks;
	Dashboard *m_dashboard;		/* attention: pour le moment doit etre construit apres talks pour beneficier de SDL_TTF */

	unsigned int m_time;					/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */


	void update_camera();       /* MàJ cam */
	void update_events_manager();
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
