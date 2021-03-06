#ifndef _EVENT_KEYBOARD_H
#define _EVENT_KEYBOARD_H


#include <string>

#include "util/enums.h"

#include <SFML/Window.hpp>


/*!
*	@class EventKeyboard
*	@brief Encapsulation d'un evenement SFML
*/
class EventKeyboard
{
protected:
    sf::Event m_event;
    bool m_treated;
    bool m_ctrl;
    bool m_altGr;
    bool m_capsLockOn;
    bool m_shift;

public:
    /*!
    *	@brief Constructeur
    *
    *	Comportement de l'objet indéfini tant qu'on initialise pas l'event,
    *	par exemple avec pollEvent ou waitEvent
    */
    EventKeyboard();

    /*!
    *	@brief Constructeur de copie
    */
    EventKeyboard (const EventKeyboard &eventKeyboard);

    /*!
    *	@brief Constructeur
    *	@param event L'evenement a encapsuler
    */
    EventKeyboard (sf::Event event);

    /*!
    *	@brief Destructeur
    */
    ~EventKeyboard();

    static bool pollEvent (EventKeyboard *event);
    static void setKeyRepeat (bool repeat);
    static void initEventKeyboard();

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'evenement represente une demande de quitter le programme
    */
    bool keyLeave() const;

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
    sf::Event getSFMLEvent() const;

    /*!
    *	@brief Accesseur
    *	@return Le nom de la touche enfoncee
    */
    std::string getKeyString() const;

    /*!
    *	@brief Accesseur
    *	@return Vrai si le touche est une touche du menu
    */
    bool isMenuKey() const;

    /*!
    *	@brief Accesseur
    *	@return Le menu_key correspondant a la touche
    *
    *	Si aucun menu_key ne correspond, comportememnt indefini
    */
    menu_key getMenuKey() const;

    /*!
    *	@brief Marque l'evenement comme traite
    */
    void markTreated()
    {
        m_treated = true;
    }

    /*!
    *	@brief Accesseur
    *	@return Indique si l'evenement a ete marque comme traite
    */
    bool treated() const
    {
        return m_treated;
    }

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'event correspond a une pression sur entree
    */
    bool enterPressed() const;

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'event correspond a une pression sur entree ou tir
    */
    bool enterMenuPressed() const;

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'event correspond a une pression sur backspace
    */
    bool backspacePressed() const;

    /*!
    *	@brief Accesseur
    *	@return Le caractere unicode correspondant a l'event (si defini, cf hasUnicode)
    */
    char unicode() const;

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'unicode de l'event est affichable
    */
    bool hasUnicode() const;

    /*!
    *	@brief Accesseur
    *	@return Vrai si l'evenement est un undo (ctrl + z)
    */
    bool isUndo() const;

protected:
    /*!
    *	@brief Initialise
    */
    void initMode();

protected:
    static sf::Window *m_window;

};

#endif
