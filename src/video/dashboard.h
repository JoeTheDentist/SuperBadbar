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
#define DASH_DECALAGE 10

#include "../video/surface_text.h"

#include "../items/weapons.h"
#include "../video/font.h"
#include "../video/anim_text.h"

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
	Surface *m_heart;
	Surface **m_weapons_pictures;
	Rect m_lifes_pos;
	Rect m_weapons_pos;
	Surface *m_peanut;
	Font m_font;
	Anim_text * m_alert;

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
	void draw_dashboard(Camera *camera);

	/**
	 *  @brief Fonction affichant un message à l'écran
	 *  @param text : Texte à afficher
	 */
    void alert(std::string text);

    /**
     *  @brief Mets à jour l'animation de texte et la suppr si besoin
     */
    void update();

private:
	void clear_dashboard();

};


#endif
