/**
 * 	@file TexturesManager.h
 * 	@brief Implémentation de la classe TexturesManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "../util/debug.h"
#ifdef _OPENGL_ACTIVE_

#include <iostream>
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_image.h"
#include <stdint.h>


#include "TexturesManager.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "Texture.h"

TexturesManager::TexturesManager()
{
	PRINT_CONSTR(1, "Construction d'un pictures_container");
}

TexturesManager::~TexturesManager()
{
	std::map<std::string, Texture*>::iterator it;
	for (it = m_container.begin(); it != m_container.end(); it++) {
		delete(it->second);
	}
	PRINT_CONSTR(1, "Destruction d'un TexturesManager");
}

Texture *TexturesManager::load_IMG(std::string key)
{
    /*const char * test = key.c_str();*/
	std::map<std::string, Texture*>::iterator it = m_container.find(key);
	Texture *texture = NULL;
	if (it == m_container.end()) {
        texture = forceLoadImg(key);
		m_container.insert(std::pair<std::string, Texture*>(key, texture));
	} else {
		texture = (*it).second;
	}
	return texture;
}

// code from http://gpwiki.org/index.php/SDL:Tutorials:Using_SDL_with_OpenGL
Texture *TexturesManager::forceLoadImg(std::string str)
{
	GLuint texture;			// This is a handle to our texture object
	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;
	int h, w;
	if ( (surface = IMG_Load(str.c_str())) ) { 
//~ 		// Check that the image's width is a power of 2
//~ 		if ( (surface->w & (surface->w - 1)) != 0 ) {
//~ 			printf("warning: image.bmp's width is not a power of 2\n");
//~ 		}
//~ 	 
//~ 		// Also check if the height is a power of 2
//~ 		if ( (surface->h & (surface->h - 1)) != 0 ) {
//~ 			printf("warning: image.bmp's height is not a power of 2\n");
//~ 		}
	 
		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4) {  // contains an alpha channel
			if (surface->format->Rmask == 0x000000ff)
					texture_format = GL_RGBA;
			else
					texture_format = GL_BGRA;
		} else if (nOfColors == 3) {     // no alpha channel
			if (surface->format->Rmask == 0x000000ff)
					texture_format = GL_RGB;
			else
					texture_format = GL_BGR;
		} else {
			printf("warning: the image is not truecolor..  this will probably break\n");
			// this error should not go unhandled
		}
	 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	 
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
						  texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	} else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}    
	 
	// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		w = surface->w;
		h = surface->h;
		SDL_FreeSurface( surface );
		return new Texture(texture, w, h);
	}
	return NULL;
}

#endif // #idef _OPENGL_ACTIVE_
