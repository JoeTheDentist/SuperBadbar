/**
 * Classe StaticData: classe singleton contenant toutes les données d'un niveau
 * ne variant pas au cours d'un cycle de jeu.
 *
**/

#ifndef _StaticData_
#define _StaticData_

#include <list>
#include <string>

class Static;
class Projectiles;
class Monster;
class GameEngine;
class Camera;
class PicturesContainer;
class Surface;

/**
 *  TOCOMMENT
 *  @class StaticData
 *  @brief 
 *	@todo REORGANISER CE BAZAR
 */
class StaticData {

private:
	Surface * m_background;             /* image de fond du niveau */
	std::list<Static*> m_statics_back;				/* liste des statics derrière sprites */
	std::list<Static*> m_statics_first;               /* liste des statics devant sprites */
	PicturesContainer *m_pictures_container;
	std::string m_level_name;
public:
        /**
         *  TOCOMMENT
         *  @brief
         */
        StaticData();

        /**
         *  TOCOMMENT
         *  @brief
         */
        ~StaticData();

        /**
         *  TOCOMMENT
         *  @brief
         */
	void init_StaticData(unsigned int lvl);

        /**
         *  TOCOMMENT
         *  @brief
         */
	void init_StaticData(std::string level_name); /* level name est un chemin vers le level */

        /**
         *  TOCOMMENT
         *  @brief
         */
        Surface * background();

        /**
         *  TOCOMMENT
         *  @brief
         */
        unsigned int StaticData_height();

        /**
         *  TOCOMMENT
         *  @brief
         */
        unsigned int StaticData_width();

        /**
         *  TOCOMMENT
         *  @brief
         */
	PicturesContainer *get_pictures_container(); /* accesseur */

        /**
         *  TOCOMMENT
         *  @brief
         */
	void display_statics_first(Camera *camera);	    /* fonction d'affichage des statics */

        /**
         *  TOCOMMENT
         *  @brief
         */
	void display_statics_back(Camera *camera);	    /* fonction d'affichage des statics */

        /**
         *  TOCOMMENT
         *  @brief
         */
	void add_static_first(Static *stat);		/* ajoute static devant sprites */

        /**
         *  TOCOMMENT
         *  @brief
         */
	void add_static_back(Static *stat);			/* ajoute static derrière sprites */

        /**
         *  TOCOMMENT
         *  @brief
         */
	std::string level_name() {return m_level_name;} /* retourne le chemin vers le level depuis le dossier de l'executable */

};

#endif
