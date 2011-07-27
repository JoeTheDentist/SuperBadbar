/**
 * 	@file TexturesManager.h
 * 	@brief Implémentation de la classe TexturesManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "TexturesManager.h"

#ifdef _OPENGL_ACTIVE_

#include <iostream>
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_image.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"


#include <util/repertories.h>
#include <util/globals.h>
#include <video/Camera.h>
#include <video/GraphicEngine.h>
#include <video/Texture.h>


TexturesManager::TexturesManager()
{
	PRINT_CONSTR(1, "Construction d'un pictures_container");
}

TexturesManager::~TexturesManager()
{
	{
		std::map<std::string, Texture*>::iterator it;
		for (it = m_container.begin(); it != m_container.end(); it++) {
			delete(it->second);
		}
	}
	{
		std::map<KeyMapSurfaceText, Texture *>::iterator it;
		for (it = m_textContainer.begin(); it != m_textContainer.end(); it++) {
			delete(it->second);
		}
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
			return NULL;
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
	    PRINT_DEBUG(1, "Can't load surface, NULL will be returned")
		return NULL;
	}
}

Texture *TexturesManager::loadUniformSurface(int width, int height, int r, int g, int b, int alpha)
{

	GLuint textName;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	GLubyte **pic = new GLubyte*[width * height];
	for (int i = 0; i < width * height; ++i) {
		pic[i] = new GLubyte[4];
		pic[i][0] = 255;
		pic[i][1] = 255;
		pic[i][2] = 255;
		pic[i][3] = 255;
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &textName);
	glBindTexture(GL_TEXTURE_2D, textName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 			
					GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, 
					height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
					pic);
	glDisable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	return new Texture(textName, width, height);
//~ 	SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
//~     SDL_FillRect(surface,NULL,SDL_MapRGB(gGraphics->get_camera()->sdl_screen()->format,r,g,b));
//~ 	Texture *res = SDLSurfaceToTexture(surface);
//~ 	SDL_FreeSurface(surface);
//~ 	return res;
}

Texture *TexturesManager::loadFrameSurface(int width, int height, int r, int g, int b)
{
	return NULL; //loadUniformSurface( width,  height,  r,  g,  b);
}

#endif // #idef _OPENGL_ACTIVE_
