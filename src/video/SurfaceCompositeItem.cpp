/**
 * 	@file SurfaceCompositeItem.cpp
 * 	@brief Implementation de la classe SurfaceCompositeItem
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#include "SurfaceCompositeItem.h"
#include <video/Surface.h>

SurfaceCompositeItem::SurfaceCompositeItem(	Surface *surface,
											Rect posFromCenterSurface, 
											SurfaceCompositeItem::posMode pm,
											SurfaceComposite *parent):
	m_surface(surface),
	m_posFromCenterSurface(posFromCenterSurface),
	m_posMode(pm),
	m_parent(parent)
{
	m_posFromCenterSurface.w = m_surface->h();
}

SurfaceCompositeItem::~SurfaceCompositeItem()
{
	
}

Rect SurfaceCompositeItem::getPosFromCenterSurface() const
{
	Rect res = m_posFromCenterSurface;
	res.w = m_surface->w();
	res.h = m_surface->h();
	return res;
}


Rect SurfaceCompositeItem::getPosInCompositeSurface() const
{
	switch (m_posMode) {
		case center:
			return getPosFromCenterSurface();
			break;
		default:
			break;
		
	}
	return Rect();
}
