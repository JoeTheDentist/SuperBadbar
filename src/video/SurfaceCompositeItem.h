
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

/*!
*	@class SurfaceCompositeItem
*	@brief Ensemble contenant une surface de SurfaceComposite et ses informations
*/
class SurfaceCompositeItem {
public:
	enum  posMode {top, bottom, right, left, center};

	/*!
	*	@brief Constructeur
	*	@param surface Surface
	*	@param posFromCenterSurface
	*	@param posMode
	*	@param parent
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
	*	@return Une position de l'item par rapport a la surface centrale, utilisee en fonction du posMode
	*/
	Rect getInformativePos() const;
	
	/*!
	*	@brief Accesseur
	*	@return La position de l'item par rapport a la surface centrale
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
	
	/*!
	*	@brief Mutateur
	*	@param surface La nouvelle surface
	*/
	void setSurface(Surface *surface) {m_surface = surface;}
	

	/*!
	*	@brief Mutateur
	*	@param pos La nouvelle position
	*/
	void setInformativePos(Rect pos) {m_posFromCenterSurface = pos;}
	

	/*!
	*	@brief Mutateur
	*	@param mode Le nouveau mode
	*/
	void setPosMode(SurfaceCompositeItem::posMode mode) {m_posMode = mode;}
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si l'item est l'item contenant la Surface centrale du SurfaceComposite
	*/
	bool isCenterSurface() const;
	
protected:
	Surface *m_surface;
	Rect m_posFromCenterSurface;
	SurfaceCompositeItem::posMode m_posMode;
	SurfaceComposite *m_parent;
	
};



#endif
