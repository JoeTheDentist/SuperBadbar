/**


**/

#ifndef _LEVELS_
#define _LEVELS_

#include "SDL/SDL.h"

#define BOX_SIZE 5  /* Taille des cases de la grille de colision */


class Level {
private:
	uint32_t m_level;							/* Numero du niveau */
	SDL_Surface ** m_monster_pic;	/* tableau des images des monstres présents dans le niveau*/
	SDL_Surface * m_background;     /* image de fond du niveau */
	uint32_t ** m_statics_matrix;      	/* matrice des statics */

	SDL_Surface *m_proj[4];     			/* images des projectiles dans tous les sens */

public:
	Level();																						/* Constructeur par défaut*/
	Level(uint32_t lvl);																		/* Constructeur avec précision du numéro de niveau */
	~Level();																						/* Destructeur */
	void fill_collision(uint32_t i, uint32_t j, uint32_t collision_type); 	/* remplit la case i j de la matrice des collisions */
	uint32_t collision(uint32_t i, uint32_t j);  										/* Accesseur */
	SDL_Surface * background();  														/* Accesseur */
	uint32_t level_height();  															 	/* Hauteur du niveau */
	uint32_t level_weight();   				 												/* Largeur du niveau */
	SDL_Surface * proj(uint8_t i); 														/* Renvoie l'image voulue (accesseur) */
};



#endif
