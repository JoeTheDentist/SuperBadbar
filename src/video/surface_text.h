/**
 * 	@file surface_text.h
 * 	@brief Header de la classe Surface_text
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _SURFACE_TEXT_
#define _SURFACE_TEXT_

#include "surface.h"
#include <string>

class Font;

/*!
*	@class Surface_text 
*	@brief Classe representant toute image du jeu contenant du texte (sans sa position)
*/
class Surface_text: public Surface {
	public:
	/*!
	*	@brief Constructeur
	*	@param text Le texte a afficher
	*	@param size La taille du texte a afficher
	*	@param font_name Le nom de la police (qui sera charge dans le repertoire des polices)
	*/
	Surface_text(std::string text, int size = 30, std::string font_name = "defaultfont.ttf");
	
	/*!
	*	@brief Constructeur
	*	@param text Le texte a afficher
	*	@param font La police a utiliser pour afficher le texte
	*/
	Surface_text(std::string text, Font &font);
	
	/*!
	*	@brief Destructeur
	*/
	~Surface_text();
	
};

#endif 
