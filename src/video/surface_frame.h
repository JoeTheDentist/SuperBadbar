/**
 * 	@file surface_frame.h
 * 	@brief Header de la classe Surface_frame
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */
 
 #ifndef BABAR_SURFACE_FRAME_H
 #define BABAR_SURFACE_FRAME_H
 
 #include "../video/surface.h"
 
 /*!
*	@class Surface_frame
*	@brief Surface entourant un cadre (equivalent d'un cadre de tableau)
*/
class Surface_frame: public Surface {
protected:
	int m_line_w;
	int m_line_h;
public:
	/*!
	*	@brief Constructeur
	*	@param rect La frame du cadre
	*	@param r La composante rouge de la couleur du cadre
	*	@param g La composante verte de la couleur du cadre
	*	@param b La composante bleue de la couleur du cadre
	*/
	Surface_frame(Rect rect, int r, int g, int b);
};
 
 #endif
 
 
