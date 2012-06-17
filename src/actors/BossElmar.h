/**
 * 	@file BossElmar.h
 * 	@brief Header de la classe BossElmar
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_BossElmar_
#define _BABAR_BossElmar_

#include <actors/Boss.h>

enum elmar_state {
	ELMAR_WALK, ELMAR_FIRE, ELMAR_CHARGE, ELMAR_JUMP
};

/**
 * 	@class BossElmar
 * 	@brief Elmer (premier boss)
 */
class BossElmar : public Boss {
private:
	elmar_state m_elmar_state;
	int m_fire;
	int m_wait;

	/**
	 *  @brief Si Elmar est au sol
	 *  @return bool
	 */
	bool bottom();

	/**
	 *  @brief Si Elmar est en haut
	 *  @return bool
	 */
	bool top();

	/**
	 *  @brief Si Elmar est dans le coin bas gauche
	 *  @return bool
	 */
	bool in_bottom_left_corner();

	/**
	 *  @brief Si Elmar est dans le coin bas droite
	 *  @return bool
	 */
	bool in_bottom_right_corner();

	/**
	 *  @brief Si Elmar est dans le coin haut gauche
	 *  @return bool
	 */
	bool in_top_left_corner();

	/**
	 *  @brief Si Elmar est dans le coin haur droite
	 *  @return bool
	 */
	bool in_top_right_corner();

	/**
	 *  @brief Si Elmar est au milieu en bas
	 *  @return bool
	 */
	bool in_bottom_middle();

public:

	/**
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	BossElmar(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	BossElmar(Analyser *analyserLevel);

	/**
	 *  @brief Destructeur
	 */
	~BossElmar();

	/**
	 *  @brief Mise a jour vitesse normale
	 */
	void update_speed_simple();

	/**
	 *  @brief Mise a jour vitesse si IA
	 */
	void update_speed_ia();

	/**
	 *  @brief Mise a jour
	 */
	void update();

	/**
	 *  @brief Mise a jour etat
	 */
	void update_state();

	/**
	 *  @brief Action Elmar : Charge
	 */
	void elmar_charge();

	/**
	 *  @brief Action Elmar : Fire
	 */
	void elmar_fire();

	/**
	 *  @brief Action Elmar : Jump
	 */
	void elmar_jump();

	/**
	 *  @brief Action Elmar : Attends
	 */
	bool wait(int cycles);

	/**
	 *  @brief Mort
	 */
	virtual void kill();
};

#endif
