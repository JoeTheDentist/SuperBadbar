/**


**/

#ifndef _LEVELS_
#define _LEVELS_

#include "SDL/SDL.h"
#include "sprites.h"
#include "statics.h"
#include "lists.h"

#define BOX_SIZE 5  /* Taille des cases de la grille de colision */

class Static;
class Projectiles;
class Monster;


class Level {
private:
	uint32_t m_level;							/* Numero du niveau */
	int m_nb_monsters;                          /* Nombre de monstres DIFFERENTS sur le niveau */
	SDL_Surface ** m_monsters_pics[2][4];	    /* Tableau de toutes les images de monstre : etat, gauche droite, noméro image, type de monstre */
	Monster *** m_monsters_matrix;              /* Matrice de pointeurs des monstres */
	SDL_Surface * m_background;                 /* image de fond du niveau */
	uint32_t ** m_collision_matrix;      	    /* matrice des statics */
	SDL_Rect m_last_pos;                        /* Pour se souvenir de l'ancienne prosition de la caméra */

public:
	Level();															/* Constructeur par défaut*/
	Level(uint32_t lvl);												/* Constructeur avec précision du numéro de niveau */
	~Level();															/* Destructeur */
	void fill_collision(uint32_t i, uint32_t j, uint32_t collision_type); /* remplit la case i j de la matrice des collisions */
	uint32_t collision(uint32_t x, uint32_t y);  						/* Accesseur: x et y sont en PIXELS */
	SDL_Surface * background();  										/* Accesseur */
	uint32_t level_height();  											/* Hauteur du niveau */
	uint32_t level_weight();   				 							/* Largeur du niveau */
	uint32_t down_collision_type(SDL_Rect pos);							/* retourne le type des collisions accumulées des cases situées juste sous le rectangle pos */
	uint32_t up_collision_type(SDL_Rect pos);								/* retourne le type des collisions accumulées des cases situées juste au dessus du rectangle pos */
	uint32_t left_collision_type(SDL_Rect pos);								/* retourne le type des collisions accumulées des cases situées juste à gauche du rectangle pos */
	uint32_t right_collision_type(SDL_Rect pos);								/* retourne le type des collisions accumulées des cases situées juste à droite du rectangle pos */
	bool up_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste au dessus du rectangle pos est une collision haut */
	bool down_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste en dessous du rectangle pos est une collision bas */
	bool left_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste à gauche du rectangle pos est une collision gauche */
	bool right_collision(SDL_Rect pos);									/* renvoie vrai si une des cases situées juste à droite du rectangle pos est une collision droite */
	bool double_collision(SDL_Rect pos);								/* renvoie vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle */

    void fill_monster_pic(int h, int num_image, int num_monster, char * link); /* remplit une case de la matrice des images des monstres */
    void fill_monster_stats(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed);
    void fill_monster(uint32_t i, uint32_t j, Monster * monster);

    void update();   /* Met à jour la listes des monstres et le tableau de monstres, gére les collisions */
};

bool to_delete(Monster * monster);

#endif
