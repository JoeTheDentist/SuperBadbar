/**
 * 	@file GraphicEngine.h
 * 	@brief Header de la classe GraphicEngine
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
class StaticData;
class Talks;
class Dashboard;
class PicturesContainer;
class SpritesManager;

/**
 * 	@class GraphicEngine
 * 	@brief Moteur graphique 2D du jeu
 *
 */
class GraphicEngine {
private:
	Camera *m_camera;
	Talks *m_talks;
	Dashboard *m_dashboard;
	PicturesContainer *m_pictures_container;
	SpritesManager * m_sprites;

public:
	/**
	 * 	@brief Constructeur
	 */
	GraphicEngine();

	/**
	 * 	@brief Destructeur
	 */
	~GraphicEngine();

	/**
	 * 	@brief Initialise le moteur graphique
	 *	@param game Indique si on initialise le moteur pour le jeu (vrai) ou pour le menu principal (faux)
	 *	@todo On a juste besoin du picture_container, qui doit faire partie de GraphicEngine..
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
	PicturesContainer *get_pictures_container();

	/**
	 * 	@brief Accesseur
	 *  @return Pointeur sur le SpritesManager
	 */
    SpritesManager * get_sprites_manager();

	/**
	 * 	@brief Accesseur
	 *  @return Pointeur sur le dashboard
	 */
	Dashboard *get_dashboard() {return m_dashboard;}

    /**
     *  @brief Raz de SpritesManager
     */
    void clean();

	/*!
	*	@brief Flip la camera
	*/
	void flip_camera();
};


#endif
