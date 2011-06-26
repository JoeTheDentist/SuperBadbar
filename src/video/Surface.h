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

#include "../util/Rect.h"
#include <string>

class PicturesContainer;
struct SDL_Surface;




/*!
*	@class Surface
*	@brief Classe representant toute image du jeu (sans sa position)
*/
class Surface {
protected:
	SDL_Surface *m_surface;
	static PicturesContainer *m_pictures_container;
public:

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
	*	@brief Duplique la SDL surface contenue et la renvoie
	*	@return La copie
	*/
	SDL_Surface *get_copy_surface();
	/*!
	*	@brief Initialise le PicturesContainer des Surfaces
	*	@warning A appeler seulement à l'initialisation du moteur graphic
	*	@param PicturesContainer Le gestionnaire d'images
	*/
	static void set_pictures_container(PicturesContainer *PicturesContainer);

	/*!
	*	@brief Accesseur
	*	@return La largeur de l'image
	*/
	virtual int w();

	/*!
	*	@brief Accesseur
	*	@return La hauteur de l'image
	*/
	virtual int h();

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


	/*!
	*	@brief Blit l'image sur le background
	*	@param background La surface sur laquelle on blit l'image
	*	@param pos La position de blit par rapport au background (x et y comptent)
	*	@param rel_pos La taille du rectangle copie (h et w comptent)
	*/
	void blit_surface(Surface *background, Rect pos, Rect rel_pos);
	void blit_surface(Surface *background, Rect pos);

	/*!
	*	@brief Mutateur de transparence
	*	@param alpha une valeur entre 0 (transparent) et 255 (opaque)
	*/
	virtual void set_alpha(unsigned char alpha);
};

#endif
