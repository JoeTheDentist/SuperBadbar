/**
 * 	@file pictures_container.h
 * 	@brief Implémentation de la classe Pictures_container
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdint.h>


#include "pictures_container.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../util/globals.h"


Pictures_container::Pictures_container()
{
	PRINT_CONSTR(1, "Construction d'un pictures_container");
}

Pictures_container::~Pictures_container()
{
	std::map<std::string, SDL_Surface*>::iterator it;
	for (it = m_container.begin(); it != m_container.end(); it++) {
		SDL_FreeSurface(it->second);
	}
	PRINT_CONSTR(1, "Destruction d'un pictures_container");
}

SDL_Surface *Pictures_container::load_IMG(std::string key)
{
    const char * test = key.c_str();
	std::map<std::string, SDL_Surface*>::iterator it = m_container.find(key);
	SDL_Surface *surf = NULL;
	if (it == m_container.end()) {
        surf = IMG_Load((key).c_str());
		if (surf == NULL) {
			PRINT_DEBUG(1, "impossible de charger l'image %s", key.c_str());
			return NULL;
		}
		//SDL_SetColorKey(surf, SDL_SRCCOLORKEY, SDL_MapRGB(surf->format, 255, 0, 255));
		m_container.insert(std::pair<std::string, SDL_Surface*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;
}

