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

#include <SDL/SDL.h>
#include "../util/globals.h"


/**
 * 	@class Static
 * 	@brief Donnée d'une image et de sa position
 */
class Static
{
    private :
        SDL_Surface *m_image;
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
	 * 	@brief Constructeur
	 *	@param dir_image Le chemin vers l'image
	 *	@param x L'abscisse du static
	 *	@param y L'ordonnée du static
	 *	@todo Utiliser le gestionnaire d'image!
	 */		
        Static(char *dir_image, uint32_t x, uint32_t y);
		
	/**
	 * 	@brief 
	 */
        ~Static(); 
		
	/**
	 * 	@brief Accesseur
	 *	@return Un pointeur vers l'image du static
	 */
        SDL_Surface * image() const;  
	
	/**
	 * 	@brief Accesseur
	 *	@return La position du static
	 */
        Rect position() const;
};

#endif // STATICS_H_INCLUDED
