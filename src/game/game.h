
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



#define TIME_LOOP 50

class Game_engine;
class Static_data;
class Sound_engine;
class Sound_manager;
class Dashboard;
class Keyboard;
class Graphic_engine;

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
	Graphic_engine *m_graphic_engine;
	Sound_engine *m_sound_engine;
	unsigned int m_time;			/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */

	/*!
	 * 	@brief Mise à jour du moteur graphique
	*/
	void update_graphic_engine();

	/*!
	 * 	@brief Mise à jour des évenements
	*/
	void update_events_manager();

	/*!
	 *  @brief Mise à jour de la position des sprites
	*/
	void update_pos();			
	
	/*!
	 * 	@brief Mise à jour de la vitesse des sprites
	*/
	void update_speed();
	
	/*!
	 * 	@brief Rafraichissement de l'affichage
	*/
	void refresh_screen();		

	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	*/
	void play_sounds();		



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
