/**
 * 	@file surface.h
 * 	@brief Header de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SURFACE_
#define _SURFACE_

#include <string>

class Pictures_container;
struct SDL_Surface;

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

/*!
*	@class Surface
*	@brief Classe representant toute image du jeu (sans sa position)
*/
class Surface {
protected:
	SDL_Surface *m_surface;
	static Pictures_container *m_pictures_container;
public:
    /* TODO temp ! */
    std::string m_name;

	Surface():
		m_surface(NULL) {}

	/*!
	*	@brief Constructeur
	*	@param filename Le chemin du fichier à partir de la racine du projet
	*/
	Surface(std::string filename);

	/*!
	*	@brief Constructeur depuis un pointeur vers une surface
	*	@param s La surface a copier
	*/
	Surface(Surface * s);

	/*!
	*	@brief Destructeur
	*/
	~Surface();

	/*!
	*	@brief Accesseur
	*	@return L'image SDL
	*/
	SDL_Surface *get_surface();

	/*!
	*	@brief Initialise le pictures_container des Surfaces
	*	@warning A appeler seulement à l'initialisation du moteur graphic
	*	@param pictures_container Le gestionnaire d'images
	*/
	static void set_pictures_container(Pictures_container *pictures_container);

	/*!
	*	@brief Accesseur
	*	@return La largeur de l'image
	*/
	int w();

	/*!
	*	@brief Accesseur
	*	@return La hauteur de l'image
	*/
	int h();

	/*!
	*	@brief Mutateur
	*	@param La largeur de l'image
	*/
	void set_w(int w);

	/*!
	*	@brief Mutateur
	*	@return La hauteur de l'image
	*/
	void set_h(int h);

};

#endif
