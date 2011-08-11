/**
 * 	@file SfmlKeyConvertor.h
 * 	@brief Header de la classe SfmlKeyConvertor
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2010
 *
 */

#ifndef _SFMLKEYCONVERTOR_H
#define _SFMLKEYCONVERTOR_H

#include <SFML/Window.hpp>

#include <string>

class SfmlKeyConvertor {
public:
        /**
         *  @brief Destructeur
         */
	virtual ~SfmlKeyConvertor() = 0;

        /**
         *  TOCOMMENT
         *  @brief
         *  @param
         *  @return
         */
	static std::string sfmlkeyToStdstring(sf::Key::Code key);

        /**
         *  TOCOMMENT
         *  @brief
         *  @param
         *  @return
         */
	static sf::Key::Code stdstringToSfmlkey(std::string str);
};


#endif
