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
#include "../video/KeyMapSurfaceText.h"



class Texture;

/**
 * 	@class TexturesManager
 * 	@brief Charge les textures de façon à optimiser la mémoire
 *
 */
class TexturesManager {
private:
	std::map<std::string, Texture *> m_container;
	std::map<KeyMapSurfaceText, Texture *> m_textContainer;
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

	/*!
	*	@brief Retourne un pointeur vers la texture de texte demandee
	*	@param text Le texte de la surface
	*	@param size La taille du texte de la surface
	*	@param r La composante rouge du texte
	*	@param g La composante verte du texte
	*	@param b La composante bleue du texte
	*	@param fontNameLe nom de la police (qui sera charge dans le repertoire des polices)
	*	@return Un pointeur vers la texture demandee
	*/
	Texture *loadTextureText(std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string fontName = "defaultfont.ttf");
	
	
	/*!
	*	@brief Transforme une SDL_Surface en Texture 
	*	@param surface La surface a transformer
	*	@return La texture
	*/
	static Texture *SDLSurfaceToTexture(SDL_Surface *surface);
	
	Texture *loadUniformSurface(int width, int height, int r, int g, int b);
	Texture *loadFrameSurface(int width, int height, int r, int g, int b);

};

#endif // #idef _OPENGL_ACTIVE_
#endif // #ifndef _TEXTUREMSMANAGER_
