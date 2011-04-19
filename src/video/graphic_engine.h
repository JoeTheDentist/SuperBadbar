/**
 * 	@file graphic_engine.h
 * 	@brief Header de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _GRAPHIC_ENGINE_
#define _GRAPHIC_ENGINE_

#include <string>

class Camera;
class Babar;
class Static_data;
class Talks;
class Dashboard;
class Pictures_container;
class Sprites_manager;

/**
 * 	@class Graphic_engine
 * 	@brief Moteur graphique 2D du jeu
 *
 */
class Graphic_engine {
private:
	Camera *m_camera;
	Talks *m_talks;
	Dashboard *m_dashboard;
	Pictures_container *m_pictures_container;
	Sprites_manager * m_sprites;

public:
	/**
	 * 	@brief Constructeur
	 */
	Graphic_engine();

	/**
	 * 	@brief Destructeur
	 */
	~Graphic_engine();

	/**
	 * 	@brief Initialise le moteur graphique
	 *	@param game Indique si on initialise le moteur pour le jeu (vrai) ou pour le menu principal (faux)
	 *	@todo On a juste besoin du picture_container, qui doit faire partie de graphic_engine..
	 */
	void init_graphic_engine(bool game = true);

	/**
	 * 	@brief Mise à jour du moteur graphique
	 *
	 *	Met à jour la position de la camera
	 */
	void update();

	/**
	 * 	@brief Affiche le tableau de board
	 *	@param camera Le gestionnaire d'affichage
	 */
	void draw_dashboard(Camera *camera);

	/**
	 * 	@brief Affiche les sprites
	 *	@param camera Le gestionnaire d'affichage
	 */
	void display_sprites(Camera * cam);

	/**
	 *  @brief Envoie un message d'avertissement
	 *  @brief Message à envoyer
	 */
    void alert(std::string text);

	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers la camera
	 */
	Camera *get_camera();

	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers le gestionnaire de dialogues
	 */
	Talks *get_talks();

	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers le gestionnaire d'images
	 */
	Pictures_container *get_pictures_container();

	/**
	 * 	@brief Accesseur
	 *  @return Pointeur sur le sprites_manager
	 */
    Sprites_manager * get_sprites_manager();

    /**
     *  @brief Raz de sprites_manager
     */
    void clean();
};


#endif
