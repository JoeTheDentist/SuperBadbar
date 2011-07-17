/**
 * 	@file font.h
 * 	@brief Header de la classe Font
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _BABAR_FONT_
#define _BABAR_FONT_

#include <string>
#include "../../lib/SDL/include/SDL/SDL_ttf.h"
#include "../../lib/SDL/include/SDL/SDL.h"

/**
*	@class Font
*	@brief Represente une police d'ecriture (police, taille, couleur)
*
*	La classe fournit les accesseurs necessaires a SurfaceText pour ecrire du texte
*/
class Font {
	private:
	TTF_Font *m_font;
	SDL_Color m_font_color;

	public:

	/**
	*	@brief Constructeur
	*	@param size La taille de la police d'ecriture
	*	@param r La composante rouge de la police
	*	@param g La composante verte de la police
	*	@param b La	composante bleue de la police
	*	@param font_name La police a utiliser (chemin depuis le repertoire des polices)
	*/
	Font(int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");

	/**
	*	@brief Constructeur de copie
	*	@param font l'objet a copier
	*	@warning A ete defini mais ne doit pas etre appele! (affiche un message d'avertissement)
	*/
	Font(Font &font);

	/**
	*	@brief Destructeur
	*/
	~Font();

	/**
	*	@brief Accesseur sur la police ttf (police, taille mais pas couleur)
	*	@return La police ttf
	*/
	TTF_Font *get_TTF_font();

	/**
	*	@brief Accesseur sur la couleur de la police
	*	@return La couleur de la police
	*/
	SDL_Color& get_color();

	void set_color(int r, int g, int b);
};

#endif
