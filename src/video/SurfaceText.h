/**
 * 	@file SurfaceText.h
 * 	@brief Header de la classe SurfaceText
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _SURFACE_TEXT_
#define _SURFACE_TEXT_

#include <string>

#include "video/Surface.h"

class Font;

/**
*	@class SurfaceText
*	@brief Classe representant toute image du jeu contenant du texte (sans sa position)
*/
class SurfaceText: public Surface
{
protected:
    sf::String *m_stringSurface;
public:

    SurfaceText();
    /**
    *	@brief Constructeur
    *	@param text Le texte a afficher
    *	@param size La taille du texte a afficher
    *	@param r La composante rouge du texte
    *	@param g La composante verte du texte
    *	@param b La composante bleue du texte
    *	@param font_name Le nom de la police (qui sera charge dans le repertoire des polices)
    */
    SurfaceText (std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");

    /**
    *	@brief Destructeur
    */
    virtual ~SurfaceText();

    /**
    *	@brief Accesseur
    *	@return La largeur de l'image
    */
    virtual int w();

    /**
    *	@brief Accesseur
    *	@return La hauteur de l'image
    */
    virtual int h();

protected:
    virtual void init (std::string text, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");

};

#endif
