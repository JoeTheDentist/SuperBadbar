/**
 * 	@file surface.h
 * 	@brief Header de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#ifndef _SURFACE_
#define _SURFACE_

class Pictures_container;


class Surface {
//~ private:
	SDL_Surface *surface;
	static Pictures_container m_pictures_container;
public:
	Surface(std::string filename);
	~Surface();
	
	
};

#endif
