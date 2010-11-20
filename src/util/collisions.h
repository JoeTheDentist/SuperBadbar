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

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

bool check_collision(Rect A, Rect B);
bool is_up_coll(uint32_t coll_number);		/* renvoie vrai si le bit de rang 4 vaut 1 */
bool is_down_coll(uint32_t coll_number);    /* renvoie vrai si le bit de rang 3 vaut 1 */
bool is_left_coll(uint32_t coll_number);    /* renvoie vrai si le bit de rang 2 vaut 1 */
bool is_right_coll(uint32_t coll_number);   /* renvoie vrai si le bit de rang 1 vaut 1 */
bool is_climb_coll(uint32_t coll_number);   /* renvoie vrai si le bit de rang 5 vaut 1 */

#endif
