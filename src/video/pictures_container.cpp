

#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>


#include "pictures_container.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../util/repertories.h"


Pictures_container::Pictures_container()
{
	
}

Pictures_container::~Pictures_container()
{
	
}

SDL_Surface *Pictures_container::load_BMP(std::string key)
{
	std::map<std::string, SDL_Surface*>::iterator it = m_container.find(key);
	SDL_Surface *surf = NULL;
	if (it == m_container.end()) {
		surf = SDL_LoadBMP((key).c_str());
		m_container.insert(std::pair<std::string, SDL_Surface*>(key, surf));
	} else {
		surf = (*it).second;
	}
	return surf;
}

