#ifndef _STATICS_
#define _STATICS_

#include <string>
#include "windows.h"

class Static {
private:
	std::string m_name;				/* nom du static */
	uint32_t **m_collision_matrix;	/* matrice de collision du static */
	size_t m_weight;					/* largeur de la matrice de collision (en cases) */
	size_t m_height;					/* hauteur de la matrice de collision (en cases) */
public:
	Static(std::string name);										/* constructeur à partir du nom du static */
	~Static();														/* destructeur */
	void save();													/* sauvegarde les modifications dans le fichier .col */
	void display_static(Window *window);							/* blit l'image du static  */
	void display_collisions(Window *window);						/* blit l'ensemble de la grille de collisions */
	void display_square(Window *window, uint32_t x, uint32_t y);	/* blit le carré de collision séléectionné */
	void update_square(uint32_t x, uint32_t y, uint32_t coll_type);	/* mutateur de la grille */
	void reset();													/* reset la grille */
	
};

bool new_static_file(std::string static_name);	/* crée un fichier de collision vide. Si le fichier existait, il est écrasé */
												/* si le fichier bmp correspondant n'existe pas, 
												rien n'est fait et la fonction retourne false avec un message d'erreur */
#endif