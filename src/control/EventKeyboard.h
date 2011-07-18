#ifndef _EVENT_KEYBOARD_H
#define _EVENT_KEYBOARD_H

#include "../../lib/SDL/include/SDL/SDL.h"
#include <string>

/*!
*	@class EventKeyboard
*	@brief Encapsulation d'un evenement SDL
*/
class EventKeyboard {
protected:
	SDL_Event m_event;
public:
	/*!
	*	@brief Constructeur
	*	@param event L'evenement a encapsuler
	*/
	EventKeyboard(SDL_Event event);

	/*!
	*	@brief Destructeur
	*/
	~EventKeyboard();

	/*!
	*	@brief Accesseur
	*	@return Vrai si l'evenement est une touche enfoncee du clavier
	*/
	bool keyPressed() const;

	/*!
	*	@brief Accesseur
	*	@return Vrai si l'evenement est une touche relachee du clavier
	*/
	bool keyReleased() const;

	/*!
	*	@brief Accesseur
	*	@return L'evenement encapsule
	*/
	SDL_Event getSDLEvent() const;
	
	/*!
	*	@brief Accesseur
	*	@return La touche concernee au format SDLKey
	*/	
	SDLKey getSDLKey() const;
	
	/*!
	*	@brief Accesseur
	*	@return Le nom de la touche enfoncee
	*/
	std::string getKeyString() const;


//~ 	/*!
//~ 	*	@brief Accesseur 
//~ 	*	@return Vrai si le touche est une touche du menu
//~ 	*/
//~ 	bool isMenuKey() const;
//~ 	

//~ 	/*!
//~ 	*	@brief Accesseur
//~ 	*	@return Le menu_key correspondant a la touche
//~ 	*
//~ 	*	Si aucun menu_key ne correspond, comportememnt indefini
//~ 	*/
//~ 	menu_key getMenuKey() const;
};

#endif
