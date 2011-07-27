/**
 * 	@file dashboard.h
 * 	@brief Header de la classe Dashboard
 *
 * 	@author Guillaume Berard & Benoit Morel
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
#define LIFE_BAR_W 200
#define LIFE_BAR_H 20

#include <string>

#include <util/Rect.h>

class Camera;
class Babar;
class Font;
class PicturesContainer;
class Surface;
class SurfaceText;
class Weapon;
class AnimText;
class LifeBarPossessor;

/**
 * 	@class Dashboard
 * 	@brief Tableau de bord du jeu
 *
 *	@todo A deplacer dans GraphicEngine
 */
class Dashboard {
private:
	Surface *m_heart;
	Surface **m_weapons_pictures;
	Rect m_HP_pos;
	Rect m_weapons_pos;
	Surface *m_peanut;
	Surface *m_babar_head;
	int m_sizeFont;
	int m_rFont;
	int m_gFont;
	int m_bFont;
	std::string m_nameFont;
	AnimText * m_alert;
	LifeBarPossessor *m_life_bar_possessor;
	Surface *m_green_rect;
	Surface *m_red_rect;
	Surface *m_life_bar;
	Rect m_frame_life_bar;
	Rect m_rect_null;

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
	 *	@param PicturesContainer Gestionnaire de chargement d'images
	 */
	void init_dashboard(PicturesContainer *PicturesContainer);

	/**
	 * 	@brief Affiche le tableau de board
	 * 	@param HP Le nombre de vies de Babar
	 *	@param camera Le gestionnaire d'affichage
	 *	@param babar Pointeur vers babar
	 */
	void draw_dashboard(Camera *camera);

	/**
	 *  @brief Fonction affichant un message Ã  l'Ã©cran
	 *  @param text : Texte Ã  afficher
	 */
    void alert(std::string text);

    /**
     *  @brief Mets Ã  jour l'animation de texte et la suppr si besoin
     */
    void update();

	void set_life_bar_possessor(LifeBarPossessor *lfb) {m_life_bar_possessor = lfb;}

	void remove_life_bar_possessor() {m_life_bar_possessor = NULL;}

private:
	void clear_dashboard();

};


#endif
