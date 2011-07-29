
/**
 * 	@file SurfaceCompositeItem.h
 * 	@brief Header de la classe SurfaceCompositeItem
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef _SURFACE_COMPOSITE_ITEM_H_
#define _SURFACE_COMPOSITE_ITEM_H_

class SurfaceComposite;
class Surface;
#include <util/Rect.h>


class SurfaceCompositeItem {
public:
	enum  posMode {up, down, right, left, center};

	/*!
	*	@brief Constructeur
	*	@param surface Surface
	*	@param posFromCenterSurface
	*	@param posMode
	*	@
	*/
	SurfaceCompositeItem(	Surface *surface,
							Rect posFromCenterSurface, 
							SurfaceCompositeItem::posMode pm ,
							SurfaceComposite *parent);
	
	/*!
	*	@brief Destructeur
	*/
	~SurfaceCompositeItem();
	
	/*!
	*	@brief Accesseur
	*	@return La surface contenue
	*/
	Surface *getSurface() const {return m_surface;}
	
	/*!
	*	@brief Accesseur
	*	@return La position de l'item par rapport a la surface centrale, utilisee en fonction du posMode
	*/
	Rect getPosFromCenterSurface() const;
	
	/*!
	*	@brief Accesseur
	*	@return La veritable position de l'item par rapport au coin haut gauche de la surface composite
	*
	*	@todo NOT IMPLEMENTED
	*/
	Rect getPosInCompositeSurface() const;
	
	/*!
	*	@brief Accesseur
	*	@return Le posMode de l'item
	*/
	SurfaceCompositeItem::posMode getPosMode() const;
	
protected:
	Surface *m_surface;
	Rect m_posFromCenterSurface;
	SurfaceCompositeItem::posMode m_posMode;
	SurfaceComposite *m_parent;
	
};



#endif
