/**
 * 	@file PicturesContainer.h
 * 	@brief Header de la classe PicturesContainer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _PICTURES_CONTAINER_
#define _PICTURES_CONTAINER_

#include <map>
#include <string>
#include <iostream>

#include "../../lib/SDL/include/SDL/SDL.h"

/**
 * 	@class PicturesContainer
 * 	@brief Charge les images de façon à optimiser la mémoire
 *
 *	Fournit une méthode load_IMG qui charge une image en fonction
 *	de son chemin, stocke cette image et en renvoie un pointeur.
 *	Si cette image a déjà été chargé une fois, la méthode renvoie
 *	un pointeur vers l'image déjà chargée.
 *
 *	PicturesContainer utilise un map pour stocker et retrouver
 *	les images en fonction de leur chemin.
 *
 *	@todo reorganiser la ou les localisations de PicturesContainer dans les autres classes
 *
 */
class PicturesContainer {
private:
	std::map<std::string, SDL_Surface*> m_container;
public:
	/**
	 * 	@brief Constructeur
	 */
	PicturesContainer();

	/**
	 * 	@brief Destructeur
	 */
	~PicturesContainer();

	/**
	 * 	@brief Retourne un pointeur vers l'image demandée
	 *	@param key Le chemin vers l'image
	 *	@return Un pointeur vers l'image voulue
	 */
	SDL_Surface *load_IMG(std::string key);
};


#endif
