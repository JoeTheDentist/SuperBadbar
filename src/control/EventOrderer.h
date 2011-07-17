/**
 * 	@file EventOrderer.h
 * 	@brief Header de la classe EventOrderer
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2010
 *
 */

#ifndef _BABAR_EventOrderer_H
#define _BABAR_EventOrderer_H

#include "../../lib/SDL/include/SDL/SDL.h"
#include <string>

class Keyboard;

/**
 *  TOCOMMENT
 *  @class
 *  @brief
 */
class EventOrderer {

protected:
	SDLKey m_event;
	bool m_event_recieved;
public:
        /**
         *  @brief Constucteur
         */
	EventOrderer();

        /**
         *  TOCOMMENT
         *  @brief
         *  @param keyboard :
         */
        void order_event(Keyboard *keyboard);

        /**
         *  TOCOMMENT
         *  @brief
         *  @return
         */
	bool event_recieved();

        /**
         *  TOCOMMENT
         *  @brief
         *  @param event :
         */
	void answer_event_order(SDLKey event);

        /**
         *  TOCOMMENT
         *  @brief
         *  @return
         */
	SDLKey get_event();

        /**
         *  TOCOMMENT
         *  @brief
         *  @return
         */
	std::string get_string_event();

};

#endif
