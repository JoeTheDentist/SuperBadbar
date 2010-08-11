/**
 * Fonctions de tests de collisions
 * Un nombre de collision caractérise la collision: on regarde les
 * 4 derniers bits: 1 signifie collision et 0 absence de collision
 * le bit de poids fort représente haut, puis bas, puis gauche, puis droite pour 
 * le bit de poids faible
 **/

#ifndef _COLLISIONS_
#define _COLLISIONS_

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

bool check_collision(SDL_Rect A, SDL_Rect B);
bool up_collision(uint32_t coll_number);			/* renvoie vrai si le bit de rang 4 vaut 1 */
bool down_collision(uint32_t coll_number);      /* renvoie vrai si le bit de rang 3 vaut 1 */
bool left_collision(uint32_t coll_number);         	/* renvoie vrai si le bit de rang 2 vaut 1 */
bool right_collision(uint32_t coll_number);       /* renvoie vrai si le bit de rang 1 vaut 1 */

#endif