/**
 * 	@file MenuActionString.h
 * 	@brief Header de la classe MenuActionString
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_STRING_
#define _BABAR_MENU_ACTION_STRING_

#include <string>
#include "menus/MenuAction.h"
#include "control/Keyboard.h"
#include "control/InputString.h"


/*!
*	@class MenuActionString
*	@brief Bouton de menu permettant la saisie de texte par l'utilisateur
*/
class MenuActionString: public MenuAction
{
protected:
    InputString m_currentString;
    InputString m_backupString; // escape annule la saisie et revient sur le backup
    bool m_waitingForInput;
public:
    /**
    *	@brief Constructeur
    *	@param str Le texte de l'action (par ex "new game" ou "option")
    *	@param i L'indice de l'action (en general son numero dans la liste d'actions)
    *	@param val La valeur de depart
    */
    MenuActionString (std::string str, int i, std::string val);

    /*!
    *	@brief Maj du bouton (a appeler a chaque cycle)
    */
    virtual void update();

    /*!
    *	@brief Accesseur
    *	@return La string correspondant a la touche choisie
    */
    virtual std::string get_string() const;

    /*!
    *	@brief Traite l'evenement eventKeyboard recu
    *	@param eventKeyboard L'evenement recu
    *
    *	Si l'evenement est vraiment traite, il sera marque comme
    *	traite apres l'appel
    */
    virtual void treatEvent (EventKeyboard *eventKeyboard);

protected:
    virtual void update_text();
};



#endif
