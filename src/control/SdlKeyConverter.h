/**
 * 	@file SdlKeyConverter.h
 * 	@brief Header de la classe SdlKeyConverter
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2010
 *
 */

#ifndef _SdlKeyConverter_H
#define _SdlKeyConverter_H

#include <string>
#include "../../lib/SDL/include/SDL/SDL.h"

class SdlKeyConverter {
public:
        /**
         *  @brief Destructeur
         */
	virtual ~SdlKeyConverter() = 0;

        /**
         *  TOCOMMENT
         *  @brief
         *  @param
         *  @return
         */
	static std::string sdlkey_to_stdstring(SDLKey key);

        /**
         *  TOCOMMENT
         *  @brief
         *  @param
         *  @return
         */
	static SDLKey stdstring_to_sdlkey(std::string str);
};


#endif
