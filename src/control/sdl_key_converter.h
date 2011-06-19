#ifndef _SDL_KEY_CONVERTER_H
#define _SDL_KEY_CONVERTER_H

#include <string>
#include "../../lib/SDL/include/SDL/SDL.h"

class Sdl_key_converter {
public:
	virtual ~Sdl_key_converter() = 0;
	static std::string sdlkey_to_stdstring(SDLKey key);
	static SDLKey stdstring_to_sdlkey(std::string str);
};


#endif
