/**
 * 	@file PicturesContainer.h
 * 	@brief Implémentation de la classe PicturesContainer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_image.h"
#include <stdint.h>


#include "PicturesContainer.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../util/globals.h"


PicturesContainer::PicturesContainer()
{
	PRINT_CONSTR(1, "Construction d'un PicturesContainer");
}

PicturesContainer::~PicturesContainer()
{
	std::map<std::string, SDL_Surface*>::iterator it;
	for (it = m_container.begin(); it != m_container.end(); it++) {
		SDL_FreeSurface(it->second);
	}
	PRINT_CONSTR(1, "Destruction d'un PicturesContainer");
}

SDL_Surface *PicturesContainer::load_IMG(std::string key)
{
    /*const char * test = key.c_str();*/
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

