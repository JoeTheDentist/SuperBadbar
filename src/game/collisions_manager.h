/**
 * ATTENTION: beaucoup de vérifications sont faites pour éviter les segfaults en cas de dépassement de tableau
 * ces vérifications peuvent doubler le temps de calcul ou masquer des dépassements de tableau qui ne devraient pas
 * avoir lieu
*/

#ifndef _COLLISIONS_MANAGER_
#define _COLLISIONS_MANAGER_

#include <stdint.h>
#include "../util/globals.h"
#include "../util/lists.h"

class Static;

class Collisions_manager {
private:
	uint32_t ** m_collisions_matrix;      	/* matrice des statics */
	uint32_t m_collisions_matrix_w;
	uint32_t m_collisions_matrix_h;

public:
	Collisions_manager();
	~Collisions_manager();
	void init_collisions_manager(int level);
	static bool check_collision(Rect A, Rect B);


	uint32_t collision(uint32_t x, uint32_t y);  						/* Accesseur: x et y sont en PIXELS */
	uint32_t down_collision_type(Rect pos);							/* retourne le type des collisions accumulées des cases situées juste sous le rectangle pos */
	uint32_t up_collision_type(Rect pos);							/* retourne le type des collisions accumulées des cases situées juste au dessus du rectangle pos */
	uint32_t left_collision_type(Rect pos);							/* retourne le type des collisions accumulées des cases situées juste à gauche du rectangle pos */
	uint32_t right_collision_type(Rect pos);						/* retourne le type des collisions accumulées des cases situées juste à droite du rectangle pos */
	bool up_collision(Rect pos);									/* renvoie vrai si une des cases situées juste au dessus du rectangle pos est une collision haut */
	bool down_collision(Rect pos);									/* renvoie vrai si une des cases situées juste en dessous du rectangle pos est une collision bas */
	bool left_collision(Rect pos);									/* renvoie vrai si une des cases situées juste à gauche du rectangle pos est une collision gauche */
	bool right_collision(Rect pos);									/* renvoie vrai si une des cases situées juste à droite du rectangle pos est une collision droite */
	bool double_collision(Rect pos);								/* renvoie vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle */

};



#endif
