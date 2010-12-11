
/**
 * 	@file game.h
 * 	@brief header de la classe Game
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _GAME_
#define _GAME_
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

/**
 * 	@class Game
 * 	@brief Classe gérant l'exécution d'un niveau complet
 *
 *	Contient la boucle de jeu principale ainsi que les principaux modules:
 *	moteur de jeu, moteur graphique, moteur de son, récupération des entrées
 *	clavier, données du niveau.
 */
class Game {
private:
	Sound_manager *m_sound_manager;
	Keyboard *m_keyboard;
	Static_data *m_static_data;
	Game_engine *m_game_engine;
	Camera *m_camera;				
	Talks *m_talks;
	Dashboard *m_dashboard;		/* attention: pour le moment doit etre construit apres talks pour beneficier de SDL_TTF */

	unsigned int m_time;			/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */

	/*
	 * Mise à jour de la camera
	*/
	void update_camera();

	/*
	 * Mise à jour des évenements
	*/
	void update_events_manager();

	/*
	 *  Mise à jour de la position des sprites
	*/
	void update_pos();			
	
	/*
	 * Mise à jour de la vitesse des sprites
	*/
	void update_speed();
	
	/*
	 * Rafraichissement de l'affichage
	*/
	void refresh_screen();		



public:

	/**
	 * @brief Constructeur
	*/
	Game();

	/**
	 * @brief Destructeur
	*/
	~Game();

	/**
	 * @brief La boucle de jeu
	*/
	void game_loop();			

	/**
	 * @brief check les collisions monstres/projectiles
	*/
	void check_monsters();	
};


#endif
