/**
 * 	@file menu_action_integer.h
 * 	@brief Header de la classe Menu_action_integer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_INTEGER_
#define _BABAR_MENU_ACTION_INTEGER_

#include "../menus/menu_action.h"

class Menu_action_integer: public Menu_action {
protected:
	int m_value;
	int m_valmin;
	int m_valmax;
	int m_step;
public:
	/*!
	*	@brief Constructeur
	*	@param str Le texte de l'action (par ex "new game" ou "option")
	*	@param i L'indice de l'action (en general son numero dans la liste d'actions)
	*	@param val La valeur de depart 
	*	@param valmin La valeur minimale
	*	@param valmax La valeur maximale
	*	@param step Le pas de valeur 
	*/
	Menu_action_integer(std::string str, int i, int val = -1, int valmin = 0, int valmax = 99, int step = 5);

	virtual void incr_value(int value);
	virtual int get_value() {return m_value;}
	
protected:
	virtual void update_text();
	
};



#endif
