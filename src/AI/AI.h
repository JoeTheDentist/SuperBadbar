/**
 * 	@file AI.h
 * 	@brief Header de la classe AI
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date janvier 2011
 *
 */

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <items/Weapon.h> /* pour enum */
#include <util/Rect.h>


#define ESTIM_SPEED 10
#define WEIGHT_PROJ 100
#define DIST_WEIGHT 100

/**
 *  @class AI
 *  @brief Classe evaluant le comportement intelligent de certains monstres
 *
 *  Cette classe est liee a un monstre (ptr sur sa position)
 *  et cherche a se rapprocher de Badbar (todo, le joueur le plus proche)
 *  tout en evitant les projectiles (todo, les projectiles ennemis)
 */
class AI {
private:
	Rect * m_pos;

	/**
		 *  @brief Evaluation de la direction consideree
		 *  @param d : direction a prendre en compte
		 *  @return poids (sens AI, choix) de le direction
		 */
	double eval(Direction d);

	/**
		 *  @brief Verifie s'il y a collision
		 *  @param A : Rectange 1
		 *  @param B : Rectangle 2
		 *  @return s'il y a collision ou non
		 */
	bool check_collision(Rect A, Rect B);

	/**
		 *  @brief Evaluation en haut
		 *  @return poids (sens AI, choix) de le direction
		 */
	double eval_up();

	/**
		 *  @brief Evaluation en bas
		 *  @return poids (sens AI, choix) de le direction
		 */
	double eval_down();

	/**
		 *  @brief Evaluation a gauche
		 *  @return poids (sens AI, choix) de le direction
		 */
	double eval_left();

	/**
		 *  @brief Evaluation a droite
		 *  @return poids (sens AI, choix) de le direction
		 */
	double eval_right();

public:
	/**
		 *  @brief Construction
		 *  @param Position du monstre qui a l'IA
		 */
	AI(Rect * pos);

	/**
		 *  @brief Destructeur
		 */
	~AI();

	/**
		 * @brief donne la direction a suivre
		 * @return direction
		 */
	Direction dir();
};

#endif // AI_H_INCLUDED
