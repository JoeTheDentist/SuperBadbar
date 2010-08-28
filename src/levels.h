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
	int m_nb_monsters;                          /* Nombre de monstres sur le niveau */
	SDL_Surface ** m_monsters_pics[3][3][3];	/* Tableau de toutes les images de monstre : etat, gauche droite, noméro image, type de monstre */
	Monster ** m_monsters_matrix;               /* Matrice des monstres */
	SDL_Surface * m_background;                 /* image de fond du niveau */
	uint32_t ** m_collision_matrix;      	        /* matrice des statics */
	SDL_Rect m_last_pos;                        /* Pour se souvenir de l'ancienne prosition de la caméra */

public:
	Level();															/* Constructeur par défaut*/
	Level(uint32_t lvl);												/* Constructeur avec précision du numéro de niveau */
	~Level();															/* Destructeur */
	void fill_collision(uint32_t i, uint32_t j, uint32_t collision_type); /* remplit la case i j de la matrice des collisions */
	uint32_t collision(uint32_t i, uint32_t j);  						/* Accesseur */
	SDL_Surface * background();  										/* Accesseur */
	uint32_t level_height();  											/* Hauteur du niveau */
	uint32_t level_weight();   				 							/* Largeur du niveau */
	bool down_collision(SDL_Rect pos);
	bool up_collision(SDL_Rect pos);

    void fill_monster_pic(int state, int h, int num_image, int num_monster, char * link); /* remplit une case de la matrice des images desmonstres */
    void fill_monster_pos(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed);
    void fill_monster(uint32_t i, uint32_t j, Monster monster);

    void update();   /* Met à jour la listes des monstres et le tableau de monstres, gére les collisions */
};

bool to_delete(Monster * monster);

#endif
