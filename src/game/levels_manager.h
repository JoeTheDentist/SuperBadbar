
/**
 * 	@file levels_manager.h
 * 	@brief header de la classe Levels_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _LEVELS_MANAGER_H_
#define _LEVELS_MANAGER_H_

class Game;

class Levels_manager {
private:
	int m_level;
	Game *m_game;
public:
	Levels_manager();
	~Levels_manager();
	void play();
};


#endif
