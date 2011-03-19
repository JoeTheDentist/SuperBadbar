
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

enum result_game {
	victory, defeat, leave
};

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
	unsigned int m_time;			/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */

public:

	/**
	 * 	@brief Constructeur utilisé par le jeu
	 *	@param level Le numero du niveau actuel
	 * 	@param record_on Indique si on doit sauvegarder la sequence de touches
	 *	@param replay_on Indique si on doit charger une sequence de touches
	 *	@param Nom du fichier dans lequel on doit sauvegarder la sequence de touches
	 *	@param Nom du fichier depuis lequel on doit charger la sequence de touches
	 *
	 *	Pour une execution normale, appeler game avec false, false, "", "" (valeurs par défaut)
	*/
	Game(int level, bool record_on = false, bool replay_on = false, std::string output_name = "", std::string input_name = "");

	
	/*!
	 *	@brief Constructeur utilise par l'editeur
	 *	@param level_name Chemin vers le niveau a ouvrir (depuis la racine)
	*/
	Game(std::string level_name);

	/**
	 * @brief Destructeur
	*/
	~Game();

	/**
	 * @brief La boucle de jeu
	 * @return Le resultat du joueur
	*/
	result_game game_loop();

	/**
	 * @brief check les collisions monstres/projectiles
	*/
	void check_monsters();
	
private:
	void init_game(std::string level_name);

	/*!
	 * 	@brief Mise à jour du moteur graphique et rafraichissement de l'écran
	*/
	void update_graphic();

	/*!
	 *  @brief Mise à jour des données du jeu
	*/
	void update_game();

	/*!
	 *  @brief Mise à jour des evenements claviers
	*/
	void update_keyboard();

	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	*/
	void play_sounds();	
	
	/*!
	 *	@brief Affiche l'écran de victoire
	 *	
	 *	TODO a faire!
	*/
	void play_victory();
};


#endif
