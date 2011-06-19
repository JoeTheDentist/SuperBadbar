/**
 * 	@file menu_action_classic.h
 * 	@brief Header de la classe Menu_action_classic
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_CLASSIC_
#define _BABAR_MENU_ACTION_CLASSIC_

#include "../menus/menu_action.h"

class Menu_action_classic: public Menu_action {
public:
	/*!
	*	@brief Constructeur
	*	@param str Le texte de l'action (par ex "new game" ou "option")
	*	@param i L'indice de l'action (en general son numero dans la liste d'actions)
	*/
	Menu_action_classic(std::string str, int i);

	
};



#endif
