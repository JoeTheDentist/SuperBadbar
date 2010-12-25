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

class Surface {
private:
	SDL_Surface *m_surface;
	static Pictures_container *m_pictures_container;
public:

	/*!
	*	@brief Constructeur
	*	@param filename Le chemin du fichier à partir de la racine du projet
	*/
	Surface(std::string filename);

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
	
};

#endif
