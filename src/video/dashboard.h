/**
 * 	@file dashboard.h
 * 	@brief Header de la classe Dashboard
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _DASHBOARD_
#define _DASHBOARD_

#define POS_HEART_X 50
#define POS_HEART_Y 20
#define POS_WEAPON_X 50
#define POS_WEAPON_Y 60

#ifdef WIN32
    #include "../../lib/SDL/include/SDL/SDL_ttf.h"
#else
    #include <SDL/SDL_ttf.h>
#endif

#include "../items/weapons.h"

class Camera;
class Babar;
class Pictures_container;
class Surface;

/**
 * 	@class Dashboard
 * 	@brief Tableau de bord du jeu
 *
 *	@todo A deplacer dans Graphic_engine
 */
class Dashboard {
private:
	TTF_Font *m_font;
	SDL_Color m_font_color;
	Surface *m_heart;
	Surface **m_weapons_pictures;
	Rect m_lifes_pos;
	Rect m_weapons_pos;
public:

	/**
	 * 	@brief Constructeur
	 */
	Dashboard();

	/**
	 * 	@brief Destructeur
	 */
	~Dashboard();

	/**
	 * 	@brief Initialise le tableau de board
	 *	@param pictures_container Gestionnaire de chargement d'images
	 */
	void init_dashboard(Pictures_container *pictures_container);

	/**
	 * 	@brief Affiche le tableau de board
	 * 	@param lifes Le nombre de vies de Babar
	 *	@param camera Le gestionnaire d'affichage
	 *	@param babar Pointeur vers babar
	 */
	void draw_dashboard(int lifes, Camera *camera, Babar *babar);

};


#endif
