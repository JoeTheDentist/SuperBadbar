/**
 * 	@file SurfaceCompositeItem.cpp
 * 	@brief Implementation de la classe SurfaceCompositeItem
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#include "SurfaceCompositeItem.h"
#include "video/Surface.h"
#include <video/SurfaceComposite.h>

SurfaceCompositeItem::SurfaceCompositeItem (	Surface *surface,
        Rect posFromCenterSurface,
        SurfaceCompositeItem::posMode pm,
        SurfaceComposite *parent) :
    m_surface (surface),
    m_posFromCenterSurface (posFromCenterSurface),
    m_posMode (pm),
    m_parent (parent)
{
    m_posFromCenterSurface.w = m_surface->h();
}

SurfaceCompositeItem::~SurfaceCompositeItem()
{

}

Rect SurfaceCompositeItem::getInformativePos() const
{
    if (isCenterSurface() )
        return Rect();
    Rect res = m_posFromCenterSurface;
    res.w = m_surface->w();
    res.h = m_surface->h();
    return res;
}

Rect SurfaceCompositeItem::getPosFromCenterSurface() const
{
    //TODO
    Rect res = getInformativePos();
    Rect centerPos (0, 0, m_parent->centerWidth(), m_parent->centerHeight() );
    if (isCenterSurface() )
    {
    }
    else
    {
        switch (m_posMode)
        {
        case center:
            break;
        case top:
            res.y -= getSurface()->h();
            res.x += centerPos.w / 2;
            res.x -= getSurface()->w() / 2;
            break;
        case bottom:
            res.y += centerPos.h;
            res.x += centerPos.w / 2;
            res.x -= getSurface()->w() / 2;
            break;
        case left:
            res.x -= getSurface()->w();
            res.y += centerPos.h / 2;
            res.y -= getSurface()->h() / 2;
            break;
        case right:
            res.x += centerPos.w;
            res.y += centerPos.h / 2;
            res.y -= getSurface()->h() / 2;
            break;
        default:
            break;
        }
    }
    return res;
}

Rect SurfaceCompositeItem::getPosInCompositeSurface() const
{
    if (isCenterSurface() )
    {
        return m_parent->centerChildPos();
    }
    else
    {
        return m_parent->centerChild()->getPosInCompositeSurface() + getPosFromCenterSurface();
    }
}

bool SurfaceCompositeItem::isCenterSurface() const
{
    return m_parent->centerChild() == this;
}
