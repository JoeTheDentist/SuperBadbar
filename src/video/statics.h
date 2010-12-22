/**
 * 	@file statics.h
 * 	@brief Header de la classe Static
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

#include "../util/globals.h"

class Surface;

/**
 * 	@class Static
 * 	@brief Donnée d'une image et de sa position
 */
class Static
{
    private :
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

		
	/**
	 * 	@brief 
	 */
        ~Static(); 
		
	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers l'image du static
	 */
		Surface * image() const;  
	
	/**
	 * 	@brief Accesseur
	 *	@return La position du static
	 */
        Rect position() const;
};

#endif // STATICS_H_INCLUDED
