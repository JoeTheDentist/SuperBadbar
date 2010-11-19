#ifndef _PICTURES_CONTAINER_
#define _PICTURES_CONTAINER_

#include <map>
#include <string>
#include <iostream>
#include <SDL/SDL.h>


class Pictures_container {
private:
	std::map<std::string, SDL_Surface*> m_container;
public:
	Pictures_container();
	~Pictures_container();
	SDL_Surface *load_BMP(std::string key);
	
};


#endif
