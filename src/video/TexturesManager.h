/**
 * 	@file TexturesManager..h
 * 	@brief Header de la classe TexturesManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _TEXTUREMSMANAGER_
#define _TEXTUREMSMANAGER_

#include "../util/debug.h"
#ifdef _OPENGL_ACTIVE_

#include <map>
#include <string>
#include <iostream>



class Texture;

/**
 * 	@class TexturesManager
 * 	@brief Charge les textures de façon à optimiser la mémoire
 *
 */
class TexturesManager {
private:
	std::map<std::string, Texture *> m_container;
public:
	/**
	 * 	@brief Constructeur
	 */
	TexturesManager();

	/**
	 * 	@brief Destructeur
	 */
	~TexturesManager();

	/**
	 * 	@brief Retourne un pointeur vers l'image demandée
	 *	@param key Le chemin vers l'image
	 *	@return Un pointeur vers la texture demandee
	 */
	Texture *load_IMG(std::string key);

private:
	Texture *forceLoadImg(std::string str);
};

#endif // #idef _OPENGL_ACTIVE_
#endif // #ifndef _TEXTUREMSMANAGER_
