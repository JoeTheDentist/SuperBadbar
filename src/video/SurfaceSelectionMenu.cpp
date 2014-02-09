
#include "SurfaceSelectionMenu.h"

#include "util/repertories.h"
#include "video/SurfaceText.h"

SurfaceSelectionMenu::SurfaceSelectionMenu (Surface *centralSurface, std::string text) :
    SurfaceComposite (centralSurface),
    m_centralSurface (centralSurface),
    m_centralSurfaceIndex (0),
    m_text (text),
    m_surfaceText (new SurfaceText (text) ),
    m_surfaceTextIndex (addChild (m_surfaceText, SurfaceCompositeItem::bottom, Rect (10, 0) ) ),
    m_leftArrow (new Surface (PIC_MENU_R + "leftarrow.png") ),
    m_leftArrowIndex (addChild (m_leftArrow, SurfaceCompositeItem::left, Rect (-30, 0) ) ),
    m_rightArrow (new Surface (PIC_MENU_R + "rightarrow.png") ),
    m_rightArrowIndex (addChild (m_rightArrow, SurfaceCompositeItem::right, Rect (30, 0) ) ) {}

SurfaceSelectionMenu::~SurfaceSelectionMenu()
{
    delete m_surfaceText;
    delete m_leftArrow;
    delete m_rightArrow;
}
