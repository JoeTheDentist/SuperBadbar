#ifndef _SURFACE_BIG_H_
#define _SURFACE_BIG_H_

#include <video/Surface.h>
#include <video/BigImage.h>

class SurfaceBig: public Surface {
public:
	SurfaceBig(std::string filename);
	/*
	*	@brief Accesseur
	*	@return La largeur de l'image
	*/
	virtual int w();

	/**
	*	@brief Accesseur
	*	@return La hauteur de l'image
	*/
	virtual int h();	
private:
	BigSprite *m_bigSprite;
	
	
	
};


#endif
