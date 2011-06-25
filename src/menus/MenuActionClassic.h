/**
 * 	@file MenuActionClassic.h
 * 	@brief Header de la classe MenuActionClassic
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_CLASSIC_
#define _BABAR_MENU_ACTION_CLASSIC_

#include "../menus/MenuAction.h"

class MenuActionClassic: public MenuAction {
public:
	/*!
	*	@brief Constructeur
	*	@param str Le texte de l'action (par ex "new game" ou "option")
	*	@param i L'indice de l'action (en general son numero dans la liste d'actions)
	*/
	MenuActionClassic(std::string str, int i);


};



#endif
