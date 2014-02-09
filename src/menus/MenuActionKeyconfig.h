/**
 * 	@file MenuActionKeyconfig.h
 * 	@brief Header de la classe MenuActionKeyconfig
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_KEYCONFIG_
#define _BABAR_MENU_ACTION_KEYCONFIG_

#include <string>
#include "menus/MenuAction.h"
#include "control/Keyboard.h"

/*!
*	@class MenuActionKeyconfig
*	@brief Bouton de menu permettant la saisie d'une touche pour configurer le clavier
*
*	Le choix du joueur se fait en appuyant sur entree puis la touche voulue quand le bouton
*	est selectionne.
*	La touche choisie peut etre recuperee avec get_string() qui renvoie la chaine correspondant
*	au nom de la touche (format sdl)
*/
class MenuActionKeyconfig: public MenuAction
{
protected:
    std::string m_value;
    key m_key;
    bool m_waitingForInput;
public:
    /**
    *	@brief Constructeur
    *	@param str Le texte de l'action (par ex "new game" ou "option")
    *	@param i L'indice de l'action (en general son numero dans la liste d'actions)
    *	@param val La valeur de depart
    *	@param k La key a modifier
    */
    MenuActionKeyconfig (std::string str, int i, std::string val, key k);

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
