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
#include "../video/KeyMapSurfaceText.h"
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
	std::map<KeyMapSurfaceText, SDL_Surface*> m_textContainer;
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

	/*!
	*	@brief Retourne un pointeur vers la surface de texte demandee
	*	@param text Le texte de la surface
	*	@param size La taille du texte de la surface
	*	@param r La composante rouge du texte
	*	@param g La composante verte du texte
	*	@param b La composante bleue du texte
	*	@param fontNameLe nom de la police (qui sera charge dans le repertoire des polices)
	*/
	SDL_Surface *loadSurfaceText(std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string fontName = "defaultfont.ttf");

	/**
	 * 	@brief Vide la memoire du picture container
	 */
	void resetMemory();
};


#endif
