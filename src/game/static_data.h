/**
 * Classe Static_data: classe singleton contenant toutes les données d'un niveau
 * ne variant pas au cours d'un cycle de jeu.
 *
**/

#ifndef _STATIC_DATA_
#define _STATIC_DATA_

#include "SDL/SDL.h"
#include "../util/lists.h"
#include "../util/globals.h"

class Static;
class Projectiles;
class Monster;
class Game_engine;
class Camera;
class Pictures_container;


class Static_data {

private:
	SDL_Surface ** m_monsters_pics[2][4];	/* Tableau de toutes les images de monstre : [etat][gauche droite][numéro image][type de monstre]*/
	SDL_Surface * m_background;             /* image de fond du niveau */
	SDL_Surface *m_proj_pics[4];			/* images des projetctiles */
	List<Static*> m_statics;				/* liste des statics du niveau */
	Pictures_container *m_pictures_container;

public:
	Static_data();														/* Constructeur par défaut*/
	~Static_data();														/* Destructeur */
	void init_static_data(uint32_t lvl);
	SDL_Surface * background();  										/* Accesseur */
	uint32_t static_data_height();  									/* Hauteur du niveau */
	uint32_t static_data_weight();   				 					/* Largeur du niveau */

    void fill_monster_pic(int h, int num_image, int num_monster, const char *link); /* remplit une case de la matrice des images des monstres */
	SDL_Surface **monster_pic(uint32_t i, uint32_t j); /* accesseur */
	SDL_Surface **proj_pics();				/* accesseur */
	Pictures_container *get_pictures_container(); /* accesseur */
	void display_statics(Camera *camera);	/* fonction d'affichage des statics */
	void add_static(Static *stat);			/* ajoute un static */
	List<Static*> *static_list();

};

#endif
