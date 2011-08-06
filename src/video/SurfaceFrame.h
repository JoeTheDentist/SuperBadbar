/**
 * 	@file SurfaceFrame.h
 * 	@brief Header de la classe SurfaceFrame
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

 #ifndef BABAR_SURFACE_FRAME_H
 #define BABAR_SURFACE_FRAME_H

 #include "video/Surface.h"

 /**
*	@class SurfaceFrame
*	@brief Surface entourant un cadre (equivalent d'un cadre de tableau)
*/
class SurfaceFrame: public Surface {
protected:
	int m_line_w;
	int m_line_h;
public:
	/**
	*	@brief Constructeur
	*	@param rect La frame du cadre
	*	@param r La composante rouge de la couleur du cadre
	*	@param g La composante verte de la couleur du cadre
	*	@param b La composante bleue de la couleur du cadre
	*/
	SurfaceFrame(Rect rect, int r, int g, int b);

	virtual ~SurfaceFrame();
};

 #endif


