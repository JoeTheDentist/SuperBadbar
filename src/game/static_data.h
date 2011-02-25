/**
 * Classe Static_data: classe singleton contenant toutes les données d'un niveau
 * ne variant pas au cours d'un cycle de jeu.
 *
**/

#ifndef _STATIC_DATA_
#define _STATIC_DATA_

#include <list>
#include "../video/surface.h"
#include "../util/globals.h"

class Static;
class Projectiles;
class Monster;
class Game_engine;
class Camera;
class Pictures_container;
class Surface;


class Static_data {

private:
	Surface * m_background;             /* image de fond du niveau */
	std::list<Static*> m_statics_back;				/* liste des statics derrière sprites */
	std::list<Static*> m_statics_first;               /* liste des statics devant sprites */
	Pictures_container *m_pictures_container;

public:
	Static_data();														/* Constructeur par défaut*/
	~Static_data();														/* Destructeur */
	void init_static_data(uint32_t lvl);
	Surface * background();  										/* Accesseur */
	uint32_t static_data_height();  									/* Hauteur du niveau */
	uint32_t static_data_weight();   				 					/* Largeur du niveau */
	Pictures_container *get_pictures_container(); /* accesseur */
	void display_statics_first(Camera *camera);	    /* fonction d'affichage des statics */
	void display_statics_back(Camera *camera);	    /* fonction d'affichage des statics */
	void add_static_first(Static *stat);		/* ajoute static devant sprites */
	void add_static_back(Static *stat);			/* ajoute static derrière sprites */

};

#endif
