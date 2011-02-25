
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
#include <string>



#define TIME_LOOP 50

class Game_engine;
class Static_data;
class Sound_engine;
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
	Keyboard *m_keyboard;
	Game_engine *m_game_engine;
	Graphic_engine *m_graphic_engine;
	unsigned int m_time;			/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */

	/*!
	 * 	@brief Mise à jour du moteur graphique et rafraichissement de l'écran
	*/
	void update_graphic();

	/*!
	 *  @brief Mise à jour des données du jeu
	*/
	void update_game();

	void update_keyboard();


	/*!
	 *  @brief Supprime objets morts (monstres, projectiles)
	*/
	void delete_dead_things();




	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	*/
	void play_sounds();



public:

	/**
	 * 	@brief Constructeur
	 * 	@param record_on Indique si on doit sauvegarder la sequence de touches
	 *	@param replay_on Indique si on doit charger une sequence de touches
	 *	@param Nom du fichier dans lequel on doit sauvegarder la sequence de touches
	 *	@param Nom du fichier depuis lequel on doit charger la sequence de touches
	 *
	 *	Pour une execution normale, appeler game avec false, false, "", ""
	*/
	Game(bool record_on, bool replay_on, std::string output_name, std::string input_name);

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
