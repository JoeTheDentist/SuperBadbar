/**
 * 	@file MenuActionSelectMap.cpp
 * 	@brief Implementation de la classe MenuActionSelectMap
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#include "MenuActionSelectMap.h"
#include <sstream>
#include <control/EventKeyboard.h>
#include "util/repertories.h"
#include <video/SurfaceSelectionMenu.h>
#include <video/SurfaceComposite.h>
#include <video/SurfaceCompositeItem.h>

MenuActionSelectMap::MenuActionSelectMap (int i) :
    MenuAction ("o", i),
    m_surfaceComposite (NULL)
{

    setSurfaceSelection (new SurfaceSelectionMenu (new Surface (PIC_STATICS_R + "block8.png"), "block") );
}

void MenuActionSelectMap::incr_value (int value)
{
    //TODO (Guillaume) Path should not depend on pic root (use macro)
    setSurfaceSelection (new SurfaceSelectionMenu (new Surface ("../res/pic/animations/drum_flower/drum_flower_0.png"), "flower") );
    update();
}

void MenuActionSelectMap::setSurfaceSelection (SurfaceSelectionMenu *surf)
{
    m_surfaceComposite = surf;
    m_interfaceForSurfaceComposite = m_surfaceComposite;
}

void MenuActionSelectMap::update_text()
{

}

Surface *MenuActionSelectMap::get_surface() const
{
    return m_interfaceForSurfaceComposite;
}

void MenuActionSelectMap::update()
{

}

void MenuActionSelectMap::treatEvent (EventKeyboard *eventKeyboard)
{
    menu_key key = eventKeyboard->getMenuKey();
    switch (key)
    {
    case mk_left:
        incr_value (-1);
        eventKeyboard->markTreated();
        break;
    case mk_right:
        incr_value (1);
        eventKeyboard->markTreated();
        break;
    default:
        break;
    }
}

