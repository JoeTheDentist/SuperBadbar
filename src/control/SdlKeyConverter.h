#ifndef _SdlKeyConverter_H
#define _SdlKeyConverter_H

#include <string>
#include "../../lib/SDL/include/SDL/SDL.h"

class SdlKeyConverter {
public:
	virtual ~SdlKeyConverter() = 0;
	static std::string sdlkey_to_stdstring(SDLKey key);
	static SDLKey stdstring_to_sdlkey(std::string str);
};


#endif
