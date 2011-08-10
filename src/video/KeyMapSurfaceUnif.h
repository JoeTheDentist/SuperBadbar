/**
 * 	@file KeyMapSurfaceUnif.h
 * 	@brief Header de la classe KeyMapSurfaceUnif
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_KEYMAPSURFACEUNIF_H_
#define _BABAR_KEYMAPSURFACEUNIF_H_

#include <string>

struct KeyMapSurfaceUnif {
public:
	/*!
	*	@brief Constructeur
	*	@param width La largeur de la surface
	*	@param height La hauteur de la surface
	*	@param r La composante rouge de la surface
	*	@param g La composante verte de la surface
	*	@param b La composante bleue de la surface
	*	@param alpha La composante alpha de la surface
	*/
	KeyMapSurfaceUnif(int width, int height, int r = 255, int g = 255, int b = 255, int alpha = 255);

	/*!
	*	@brief Destructeur	
	*/
	~KeyMapSurfaceUnif();

	bool operator<(const KeyMapSurfaceUnif &key) const;
	
public:
	int m_width;
	int m_height;
	int m_r;
	int m_g;
	int m_b;
	int m_alpha;
	
};


#endif
