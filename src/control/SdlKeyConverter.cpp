
#include "SdlKeyConverter.h"


std::string SdlKeyConverter::sdlkey_to_stdstring(SDLKey key)
{
	return std::string(SDL_GetKeyName(key));
}

SDLKey SdlKeyConverter::stdstring_to_sdlkey(std::string str)
{
	for (int i = 0; i <= int(SDLK_LAST); i++) {
		if (str == SdlKeyConverter::sdlkey_to_stdstring(SDLKey(i))) {
			return (SDLKey(i));
		}
	}
	return SDLK_LAST;
}
