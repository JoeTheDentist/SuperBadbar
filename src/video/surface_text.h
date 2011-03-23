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

class Pictures_container;
struct SDL_Surface;


/*!
*	@class Surface_text 
*	@brief Classe representant toute image du jeu contenant du texte (sans sa position)
*/
class Surface_text: public Surface {
	public:
	/*!
	*	@brief Constructeur
	*	@param text Le texte a afficher
	*/
	Surface_text(std::string text, int size = 30, std::string font_name = "defaultfont.ttf");
	
	/*!
	*	@brief Destructeur
	*/
	~Surface_text();
	
};

#endif 
