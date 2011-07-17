
/**
 * 	@file game.h
 * 	@brief header de la classe Game
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _GAME_
#define _GAME_
#include <stdint.h>
#include <iostream>
#include <string>



#define TIME_LOOP 50

class GameEngine;
class StaticData;
class SoundEngine;
class Keyboard;
class Menu;

enum result_game {
	victory, defeat, leave
};

enum game_state {
	gs_playing, gs_pause, gs_talks
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
	unsigned int m_time;			/* temps actuel */
	unsigned int m_previous_time;	/* temps depuis le dernier tour de jeu */
	Menu *m_pause;
	game_state m_state;
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


	/**
	 *	@brief Constructeur utilise par l'editeur
	 *	@param level_name nom du niveau a ouvrir (depuis le dossier des levels)
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

        /**
         *  TOCOMMENT
         *  @brief
         */
	void set_state_playing();

        /**
         *  TOCOMMENT
         *  @brief
         */
	void set_state_pause();

        /**
         *  TOCOMMENT
         *  @brief
         */
	void set_state_talks();



private:
	void init_game(std::string level_name);

	/**
	 * 	@brief Mise �  jour du moteur graphique et rafraichissement de l'écran
	*/
	void update_graphic();

	/**
	 *  @brief Mise �  jour des données du jeu
	*/
	void update_game();

	/**
	 *  @brief Mise �  jour des evenements claviers
	*/
	void update_keyboard();

	/**
	 * 	@brief Joue les sons �  jouer ce cycle
	*/
	void play_sounds();

	/**
	 *	@brief Affiche l'écran de victoire
	 *
	 *	TODO a faire!
	*/
	void play_victory();


};


#endif
