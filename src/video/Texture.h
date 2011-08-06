/**
 * 	@file Texture.h
 * 	@brief Header de la classe Texture
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_TEXTURE_H_
#define _BABAR_TEXTURE_H_

#include "util/debug.h"

#ifdef _OPENGL_ACTIVE_

#include <util/Rect.h>
#include <string>
#include "../lib/SDL/include/SDL/SDL_opengl.h"

class TexturesManager;
struct SDL_Surface;




/**
*	@class Texture
*	@brief Contient une texture et ses dimensions (equivalent d'une SDL_Surface
*	dans la version precedente)
*/
class Texture {
public:
	Texture(GLuint textre, int w, int h);
	GLuint getGlTexture() const;
	int w() const;
	int h() const;

protected:
	GLuint m_texture;
	int m_w;
	int m_h;
};

#endif //#idef _OPENGL_ACTIVE_

#endif
