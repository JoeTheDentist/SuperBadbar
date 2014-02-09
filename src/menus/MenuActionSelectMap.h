/**
 * 	@file MenuActionSelectMap.h
 * 	@brief Header de la classe MenuActionSelectMap
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */


#ifndef _BABAR_MENU_ACTION_SELECT_MAP_
#define _BABAR_MENU_ACTION_SELECT_MAP_

#include "menus/MenuAction.h"

class SurfaceSelectionMenu;

class MenuActionSelectMap: public MenuAction
{
protected:

public:
    /**
    *	@brief Constructeur
    *	@param i L'indice du button dans le menu
    */
    MenuActionSelectMap (int i);

    /*!
    *	@brief Augmente la valeur contenue dans l'integer de value * le step de l'action
    *	@param value Coefficient d'incremementation
    */
    virtual void incr_value (int value);

    /*!
    *	@brief Traite l'evenement eventKeyboard recu
    *	@param eventKeyboard L'evenement recu
    *
    *	Si l'evenement est vraiment traite, il sera marque comme
    *	traite apres l'appel
    */
    virtual void treatEvent (EventKeyboard *eventKeyboard);


    virtual Surface *get_surface() const;

    /*!
    *	@brief Maj du bouton
    */
    virtual void update();

    virtual void setSurfaceSelection (SurfaceSelectionMenu *surf);



protected:
    virtual void update_text();

protected:
    // les deux pointeurs suivants pointent sur la meme variable!
    // ne modifier que la surfaceComposite
    Surface *m_interfaceForSurfaceComposite;
    SurfaceSelectionMenu *m_surfaceComposite;
};



#endif
