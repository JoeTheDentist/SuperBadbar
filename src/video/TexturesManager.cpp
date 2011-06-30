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
#include "../../lib/SDL/include/SDL/SDL_ttf.h"
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
	std::map<std::string, Texture*>::iterator it = m_container.find(key);
	Texture *texture = NULL;
	if (it == m_container.end()) {
		SDL_Surface *surface;
		if ( (surface = IMG_Load(key.c_str())) ) { 
			texture = SDLSurfaceToTexture(surface);
			SDL_FreeSurface(surface);
		} else {
			PRINT_DEBUG(1, "Can't load %s in TexturesManager::load_IMG ", key.c_str());
		}
		m_container.insert(std::pair<std::string, Texture*>(key, texture));
	} else {
		texture = (*it).second;
	}
	return texture;
}

Texture *TexturesManager::loadTextureText(std::string text, int size, int r, int g, int b, std::string fontName)
{
	KeyMapSurfaceText key(text, size, r, g, b, fontName);
	std::map<KeyMapSurfaceText, Texture*>::iterator it = m_textContainer.find(key);
	SDL_Surface *surf = NULL;
	Texture *texture;
	if (it == m_textContainer.end()) {
		TTF_Font *font = TTF_OpenFont((FONTS_R + fontName).c_str(), size);
		SDL_Color font_color;
		font_color.r = r;
		font_color.g = g;
		font_color.b = b;
		surf = TTF_RenderText_Blended(font, text.c_str(), font_color);
		TTF_CloseFont(font);
		if (surf == NULL) {
			PRINT_DEBUG(1, "impossible de charger la surface ttf correspondant a  %s", text.c_str());
			return NULL;
		}
		texture = SDLSurfaceToTexture(surf);
		SDL_FreeSurface(surf);
		m_textContainer.insert(std::pair<KeyMapSurfaceText, Texture*>(key, texture));
	} else {
		texture = (*it).second;
	}
	return texture;
}

Texture *TexturesManager::SDLSurfaceToTexture(SDL_Surface *surface)
{
	int h, w;
	GLuint texture;			
	GLenum texture_format;
	GLint  nOfColors;
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
		PRINT_DEBUG(1, "warning: the image is not truecolor..  this will probably break\n");
	}
	glGenTextures( 1, &texture );
 	glBindTexture( GL_TEXTURE_2D, texture );
 	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
					  texture_format, GL_UNSIGNED_BYTE, surface->pixels );	
	if (surface) { 
		w = surface->w;
		h = surface->h;
		return new Texture(texture, w, h);
	} else {
		return NULL;
	}
}

#endif // #idef _OPENGL_ACTIVE_
