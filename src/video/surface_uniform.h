/**
 * 	@file surface_uniform.h
 * 	@brief Header de la classe Surface_uniform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _SURFACE_UNIFORM_
#define _SURFACE_UNIFORM_

#include "surface.h"


/*!
*	@class Surface_uniform 
*	@brief Classe representant toute image du jeu contenant une couleur uniforme
*/
class Surface_uniform: public Surface {
	public:
	/*!
	*	@brief Constructeur
	*	@param width La largeur de la surface
	*	@param height La hauteur de la surface
	*	@param r La composante rouge de la surface
	*	@param g La composante verte de la surface
	*	@param b La composante bleue de la surface
	*/
	Surface_uniform(int width, int height, int r = 255, int g = 255, int b = 255);
	
	/*!
	*	@brief Destructeur
	*/
	~Surface_uniform();
	
};

#endif 
