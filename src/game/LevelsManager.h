
/**
 * 	@file LevelsManager.h
 * 	@brief header de la classe LevelsManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _LevelsManager_H_
#define _LevelsManager_H_

class Game;

class LevelsManager {
private:
	int m_level;
	Game *m_game;
public:
	LevelsManager();
	~LevelsManager();
	void play();
	void play_defeat();
	void the_end();
};


#endif
