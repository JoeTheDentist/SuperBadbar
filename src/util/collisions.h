/**
 * 	@file collisions.h
 * 	@brief Fonctions de collisions
 *	@todo deplacer dans collision_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

/**
 * Fonctions de tests de collisions
 * Un nombre de collision caractérise la collision: on regarde les
 * 4 derniers bits: 1 signifie collision et 0 absence de collision
 * le bit de poids fort représente haut, puis bas, puis gauche, puis droite pour
 * le bit de poids faible
 **/

#ifndef _COLLISIONS_
#define _COLLISIONS_

#include <SDL/SDL.h>
#include "../util/globals.h"



bool check_collision(Rect A, Rect B);
bool is_up_coll(uint32_t coll_number);		/* renvoie vrai si le bit de rang 4 vaut 1 */
bool is_down_coll(uint32_t coll_number);    /* renvoie vrai si le bit de rang 3 vaut 1 */
bool is_left_coll(uint32_t coll_number);    /* renvoie vrai si le bit de rang 2 vaut 1 */
bool is_right_coll(uint32_t coll_number);   /* renvoie vrai si le bit de rang 1 vaut 1 */
bool is_climb_coll(uint32_t coll_number);   /* renvoie vrai si le bit de rang 5 vaut 1 */

#endif
