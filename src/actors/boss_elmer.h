/**
 * 	@file boss_elmer.h
 * 	@brief Header de la classe Boss_elmer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_BOSS_ELMER_
#define _BABAR_BOSS_ELMER_

#include "../actors/boss.h"

enum elmar_state {
    ELMAR_WALK, ELMAR_FIRE, ELMAR_CHARGE, ELMAR_JUMP
};

/**
 * 	@class Boss_elmer
 * 	@brief Elmer (premier boss)
 *
 */

class Boss_elmer : public Boss {
private:
    elmar_state m_elmar_state;
    int m_fire;
    int m_wait;

public:

	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	Boss_elmer(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Boss_elmer(Analyser *analyserLevel);

	~Boss_elmer();

	void update_speed_simple();

	void update_speed_ia();

	void update();

    bool bottom();

    bool top();

    bool in_bottom_left_corner();

    bool in_bottom_right_corner();

    bool in_top_left_corner();

    bool in_top_right_corner();

    bool in_bottom_middle();

    void update_state();

    void elmar_charge();

    void elmar_fire();

    void elmar_jump();

    bool wait(int cycles);
};



#endif


