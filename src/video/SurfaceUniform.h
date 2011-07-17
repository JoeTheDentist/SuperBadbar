/**
 * 	@file SurfaceUniform.h
 * 	@brief Header de la classe SurfaceUniform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _SURFACE_UNIFORM_
#define _SURFACE_UNIFORM_

#include "Surface.h"


/**
*	@class SurfaceUniform
*	@brief Classe representant toute image du jeu contenant une couleur uniforme
*/
class SurfaceUniform: public Surface {
	public:
	/**
	*	@brief Constructeur
	*	@param width La largeur de la surface
	*	@param height La hauteur de la surface
	*	@param r La composante rouge de la surface
	*	@param g La composante verte de la surface
	*	@param b La composante bleue de la surface
	*	@param alpha La composante alpha de la surface
	*/
	SurfaceUniform(int width, int height, int r = 255, int g = 255, int b = 255, int alpha = 255);

	/**
	*	@brief Destructeur
	*/
	virtual ~SurfaceUniform();

};

#endif
