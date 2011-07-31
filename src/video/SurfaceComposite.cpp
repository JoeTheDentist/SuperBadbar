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
	addChild(center);
	m_surface = NULL;
}


int SurfaceComposite::addChild(	Surface *surface,
								SurfaceCompositeItem::posMode pm,
								Rect posFromCenterSurface)
{
	m_children.push_back(new SurfaceCompositeItem(surface, posFromCenterSurface, pm, this));
	return m_children.size() - 1;
}

void SurfaceComposite::setSurface(unsigned int i, Surface *surface)
{
	if (m_children.size() <= i || (m_children[i] == NULL))
		return;
	m_children[i]->setSurface(surface);
}


int SurfaceComposite::w() 
{
	Surface *surface = centerChild()->getSurface();
	int x1 = 0, x2 = surface->w();
	for (std::vector<SurfaceCompositeItem *>::iterator it = m_children.begin(); 
			it != m_children.end(); ++it) {
		Rect temp = (*it)->getPosFromCenterSurface();
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
		Rect temp = (*it)->getPosFromCenterSurface();
		y1 = LOCAL_MIN(y1, temp.y);
		y2 = LOCAL_MAX(y2, temp.y + temp.h);
	}
	return y2 - y1;
}

SurfaceCompositeItem *SurfaceComposite::centerChild() const
{
	return *(m_children.begin());
}

#include <iostream>

Rect SurfaceComposite::centerChildPos() const
{
	SurfaceCompositeItem *parent = centerChild();
	Rect res(0, 0, parent->getSurface()->w(), parent->getSurface()->h());
	std::vector<SurfaceCompositeItem *>::const_iterator it = m_children.begin();
	++it; // on jump le centerWidget
	for (; it != m_children.end(); ++it) {
		res.x = -LOCAL_MIN(-res.x, (*it)->getPosFromCenterSurface().x);
		res.y = -LOCAL_MIN(-res.y, (*it)->getPosFromCenterSurface().y);
	}
	std::cout << res.x << " " << res.y << std::endl;
	return res;
}

int SurfaceComposite::centerWidth() const 
{
	return centerChild()->getSurface()->w();
}

int SurfaceComposite::centerHeight() const 
{
	return centerChild()->getSurface()->h();
}
