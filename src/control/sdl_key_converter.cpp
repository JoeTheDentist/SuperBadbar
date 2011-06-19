
#include "sdl_key_converter.h"


std::string Sdl_key_converter::sdlkey_to_stdstring(SDLKey key)
{
	return std::string(SDL_GetKeyName(key));
}

SDLKey Sdl_key_converter::stdstring_to_sdlkey(std::string str)
{
	for (int i = 0; i <= int(SDLK_LAST); i++) {
		if (str == Sdl_key_converter::sdlkey_to_stdstring(SDLKey(i))) {
			return (SDLKey(i));
		}
	}
	return SDLK_LAST;
}
