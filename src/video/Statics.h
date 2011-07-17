/**
 * 	@file statics.h
 * 	@brief Header de la classe Static
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

#include "Surface.h"
#include "Displayable.h"

class Surface;
struct Rect;

/**
 * 	@class Static
 * 	@brief Donnée d'une image et de sa position
 */
class Static: public Displayable
{
    protected :
        Surface *m_image;
        Rect m_pos;

    public :

	/**
	 * 	@brief Constructeur
	 */
    Static();

	/**
	 * 	@brief Constructeur
	 *	@param dir_image Le chemin vers l'image
	 *	@param pos La position du static
	 *	@todo Utiliser le gestionnaire d'image!
	 */
    Static(std::string dir_image, Rect pos);

    Static(Surface * img, Rect pos);

	/**
	 * 	@brief
	 */
    ~Static();

	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers l'image du static
	 */
    Surface * current_picture() const;

	/**
	 * 	@brief Accesseur
	 *	@return La position du static
	 */
    Rect position() const;
};

#endif // STATICS_H_INCLUDED
