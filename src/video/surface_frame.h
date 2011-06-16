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
public:
	Surface_frame(Rect rect, int r, int g, int b);
};
 
 #endif
 
 
