
/**
 * 	@file game_initializer.h
 * 	@brief Initialisation/Fermeture des librairies et objets globals du projet
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _GAME_INTIALIZER_H_
#define _GAME_INTIALIZER_H_


/**
 * 	@class Game_initializer
 * 	@brief Initialise et ferme les librairies et objets globaux du projet
 *
 * Initialise:
 * - SDL
 * - TTF
 * - FMOD
 * Instancie:
 * - gSound (le moteur de son)
**/

class Game_initializer {
	public:
	/*!
	* @brief Initialise le jeu
	*/
	static bool init_game();
	
	/*!
	* @brief Ferme les librairies et objets globaux du jeu
	*/	
	static bool close_game();
};



#endif
