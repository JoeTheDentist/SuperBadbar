/**
 * 	@file MenuActionKeyconfig.h
 * 	@brief Header de la classe MenuActionKeyconfig
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_KEYCONFIG_
#define _BABAR_MENU_ACTION_KEYCONFIG_

#include <string>
#include "../menus/MenuAction.h"
#include "../control/Keyboard.h"
class EventOrderer;

class MenuActionKeyconfig: public MenuAction {
protected:
	std::string m_value;
	EventOrderer *m_EventOrderer;
	key m_key;
public:
	/*!
	*	@brief Constructeur
	*	@param str Le texte de l'action (par ex "new game" ou "option")
	*	@param i L'indice de l'action (en general son numero dans la liste d'actions)
	*	@param val La valeur de depart
	*	@param k La key a modifier
	*/
	MenuActionKeyconfig(std::string str, int i, std::string val, key k);

	void change_value();

	virtual void update();

	virtual void enter_pressed();

	virtual std::string get_string();

protected:
	virtual void update_text();
};



#endif
