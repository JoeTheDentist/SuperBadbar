
/**
 * 	@file LevelsManager.h
 * 	@brief header de la classe LevelsManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _LevelsManager_H_
#define _LevelsManager_H_

class Game;

/**
 *  @class LevelsManager
 *  @brief
 *	@todo comment
 */
class LevelsManager {
private:
	int m_level;
	Game *m_game;
public:
	/**
		 *  @brief Constructeur
		 */
	LevelsManager();

	/**
		 *  @brief Destructeur
		 */
	~LevelsManager();

	/**
		 *  @brief Jeu
		 */
	void play();

	/**
		 *  @brief Active gameover
		 */
	void play_defeat();

	/**
		 *  @brief Fin
		 */
	void the_end();
};


#endif
