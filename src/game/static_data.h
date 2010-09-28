/**
 * Classe Static_data: classe singleton contenant toutes les données d'un niveau
 * ne variant pas au cours d'un cycle de jeu.
 *

**/

#ifndef _STATIC_DATA_
#define _STATIC_DATA_

#include "SDL/SDL.h"
#include "../util/lists.h"
#define BOX_SIZE 5  /* Taille des cases de la grille de colision */

class Static;
class Projectiles;
class Monster;
class Dynamic_data;
class Camera;


class Static_data {
private:
	uint32_t m_static_data;							/* Numero du niveau */
	int m_nb_monsters;                          /* Nombre de monstres DIFFERENTS sur le niveau */
	SDL_Surface ** m_monsters_pics[2][4];	    /* Tableau de toutes les images de monstre : etat, gauche droite, noméro image, type de monstre */
	SDL_Surface * m_background;                 /* image de fond du niveau */
	uint32_t ** m_collision_matrix;      	    /* matrice des statics */
	SDL_Rect m_last_pos;                        /* Pour se souvenir de l'ancienne prosition de la caméra */
	SDL_Surface *m_proj_pics[4];
	List<Static*> m_statics;


public:
	Static_data();														/* Constructeur par défaut*/
	Static_data(uint32_t lvl);											/* Constructeur avec précision du numéro de niveau */
	~Static_data();														/* Destructeur */
	void fill_collision(uint32_t i, uint32_t j, uint32_t collision_type); /* remplit la case i j de la matrice des collisions */
	uint32_t collision(uint32_t x, uint32_t y);  						/* Accesseur: x et y sont en PIXELS */
	SDL_Surface * background();  										/* Accesseur */
	uint32_t static_data_height();  									/* Hauteur du niveau */
	uint32_t static_data_weight();   				 					/* Largeur du niveau */
	uint32_t down_collision_type(SDL_Rect pos);							/* retourne le type des collisions accumulées des cases situées juste sous le rectangle pos */
	uint32_t up_collision_type(SDL_Rect pos);							/* retourne le type des collisions accumulées des cases situées juste au dessus du rectangle pos */
	uint32_t left_collision_type(SDL_Rect pos);							/* retourne le type des collisions accumulées des cases situées juste à gauche du rectangle pos */
	uint32_t right_collision_type(SDL_Rect pos);						/* retourne le type des collisions accumulées des cases situées juste à droite du rectangle pos */
	bool up_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste au dessus du rectangle pos est une collision haut */
	bool down_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste en dessous du rectangle pos est une collision bas */
	bool left_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste à gauche du rectangle pos est une collision gauche */
	bool right_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste à droite du rectangle pos est une collision droite */
	bool double_collision(SDL_Rect pos);								/* renvoie vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle */

    void fill_monster_pic(int h, int num_image, int num_monster, const char *link); /* remplit une case de la matrice des images des monstres */
	SDL_Surface **monster_pic(uint32_t i, uint32_t j); /* accesseur */
	SDL_Surface **proj_pics();
	void display_statics(Camera *camera);
	void add_static(Static *stat);

};

#endif
