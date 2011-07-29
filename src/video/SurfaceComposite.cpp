/**
 * 	@file SurfaceComposite.cpp
 * 	@brief Implementation de la classe SurfaceComposite
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */
 
#include "SurfaceComposite.h"

#include <video/Surface.h>

#define LOCAL_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define LOCAL_MAX(a, b) (((a) < (b)) ? (b) : (a))

SurfaceComposite::SurfaceComposite(Surface *center)
{
	addChildren(center);
}


void SurfaceComposite::addChildren(	Surface *surface,
									SurfaceCompositeItem::posMode pm,
									Rect posFromCenterSurface)
{
	m_surface = surface->get_surface();
	m_children.push_back(new SurfaceCompositeItem(surface, posFromCenterSurface, pm, this));
}

int SurfaceComposite::w() 
{
	Surface *surface = centerChild()->getSurface();
	int x1 = 0, x2 = surface->w();
	for (std::vector<SurfaceCompositeItem *>::iterator it = m_children.begin(); 
			it != m_children.end(); ++it) {
		Rect temp = (*it)->getPosInCompositeSurface();
		x1 = LOCAL_MIN(x1, temp.x);
		x2 = LOCAL_MAX(x2, temp.x + temp.w);
	}
	return x2 - x1;
}

int SurfaceComposite::h() 
{
	Surface *surface = centerChild()->getSurface();
	int y1 = 0, y2 = surface->h();
	for (std::vector<SurfaceCompositeItem *>::iterator it = m_children.begin(); 
			it != m_children.end(); ++it) {
		Rect temp = (*it)->getPosInCompositeSurface();
		y1 = LOCAL_MIN(y1, temp.y);
		y2 = LOCAL_MAX(y2, temp.y + temp.h);
	}
	return y2 - y1;
}

SurfaceCompositeItem *SurfaceComposite::centerChild()
{
	return *(m_children.begin());
}
