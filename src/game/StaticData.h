/**
 * Classe StaticData: classe singleton contenant toutes les données d'un niveau
 * ne variant pas au cours d'un cycle de jeu.
 *
**/

#ifndef _StaticData_
#define _StaticData_

#include <list>
#include "../video/surface.h"
#include "../util/globals.h"

class Static;
class Projectiles;
class Monster;
class GameEngine;
class Camera;
class PicturesContainer;
class Surface;


class StaticData {

private:
	Surface * m_background;             /* image de fond du niveau */
	std::list<Static*> m_statics_back;				/* liste des statics derrière sprites */
	std::list<Static*> m_statics_first;               /* liste des statics devant sprites */
	PicturesContainer *m_pictures_container;
	std::string m_level_name;
public:
	StaticData();														/* Constructeur par défaut*/
	~StaticData();														/* Destructeur */
	void init_StaticData(unsigned int lvl);
	void init_StaticData(std::string level_name); /* level name est un chemin vers le level */
	Surface * background();  										/* Accesseur */
	unsigned int StaticData_height();  									/* Hauteur du niveau */
	unsigned int StaticData_width();   				 					/* Largeur du niveau */
	PicturesContainer *get_pictures_container(); /* accesseur */
	void display_statics_first(Camera *camera);	    /* fonction d'affichage des statics */
	void display_statics_back(Camera *camera);	    /* fonction d'affichage des statics */
	void add_static_first(Static *stat);		/* ajoute static devant sprites */
	void add_static_back(Static *stat);			/* ajoute static derrière sprites */
	std::string level_name() {return m_level_name;} /* retourne le chemin vers le level depuis le dossier de l'executable */

};

#endif
