/**
 * 	@file SurfacesContainer.h
 * 	@brief Implémentation de la classe SurfacesContainer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_image.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"
#include <stdint.h>


#include "SurfacesContainer.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../video/Camera.h"


SurfacesContainer::SurfacesContainer()
{
	PRINT_CONSTR(1, "Construction d'un SurfacesContainer");
}

SurfacesContainer::~SurfacesContainer()
{
	resetMemory();
	PRINT_CONSTR(1, "Destruction d'un SurfacesContainer");
}

SDL_Surface *SurfacesContainer::load_IMG(std::string key)
{
	std::map<std::string, SDL_Surface*>::iterator it = m_container.find(key);
	SDL_Surface *surf = NULL;
	if (it == m_container.end()) {
        surf = IMG_Load((key).c_str());
		if (surf == NULL) {
			PRINT_DEBUG(1, "impossible de charger l'image %s", key.c_str());
			return NULL;
		}
		m_container.insert(std::pair<std::string, SDL_Surface*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;
}

SDL_Surface *SurfacesContainer::loadSurfaceText(std::string text, int size, int r, int g, int b, std::string fontName)
{
	KeyMapSurfaceText key(text, size, r, g, b, fontName);
	std::map<KeyMapSurfaceText, SDL_Surface*>::iterator it = m_textContainer.find(key);
	SDL_Surface *surf = NULL;
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
		m_textContainer.insert(std::pair<KeyMapSurfaceText, SDL_Surface*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;	
}


SDL_Surface *SurfacesContainer::loadSurfaceUniform(int width, int height, int r, int g, int b, int alpha)
{
	KeyMapSurfaceUnif key(width, height, r, g, b, alpha);
	std::map<KeyMapSurfaceUnif, SDL_Surface*>::iterator it = m_unifContainer.find(key);
	SDL_Surface *surf = NULL;
	if (it == m_unifContainer.end()) {
		surf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
		SDL_FillRect(surf,NULL,SDL_MapRGB(gGraphics->get_camera()->sdl_screen()->format,r,g,b));
		if (surf == NULL) {
			PRINT_DEBUG(1, "impossible de charger la surface uniforme");
			return NULL;
		}
		m_unifContainer.insert(std::pair<KeyMapSurfaceUnif, SDL_Surface*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;	
}

void SurfacesContainer::resetMemory()
{
	std::map<std::string, SDL_Surface*>::iterator it;
	for (it = m_container.begin(); it != m_container.end(); it++) {
		SDL_FreeSurface(it->second);
	}
	std::map<KeyMapSurfaceText, SDL_Surface*>::iterator ittext;
	for (ittext = m_textContainer.begin(); ittext != m_textContainer.end(); ittext++) {
		SDL_FreeSurface(ittext->second);
	}	
	std::map<KeyMapSurfaceUnif, SDL_Surface*>::iterator itunif;
	for (itunif = m_unifContainer.begin(); itunif != m_unifContainer.end(); itunif++) {
		SDL_FreeSurface(itunif->second);
	}	
}
