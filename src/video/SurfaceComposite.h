
/**
 * 	@file SurfaceComposite.h
 * 	@brief Header de la classe SurfaceComposite
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */
 
#ifndef _SURFACE_COMPOSITE_H_
#define _SURFACE_COMPOSITE_H_

#include <vector>

#include <video/SurfaceCompositeItem.h>
#include <video/Surface.h>


class SurfaceComposite: public Surface {
public:
	
	
	/*!
	*	@brief Constructeur
	*	@param center La surface centrale
	*/
	SurfaceComposite(Surface *center);
	
	/*!
	*	@brief Desctructeur
	*
	*	N'appelle PAS Les destructeurs des Surfaces contenues
	*/
	virtual ~SurfaceComposite() {}

	/*!
	*	@brief Ajoute une surface fille
	*	@param surface La surface fille
	*	@param pm  Le mode de positionnement
	*	@param posFromCenterSurface Le decalage par rapport a la position centrale en fonction
	*	du mode de positionnement
	*/
	void addChildren(	Surface *surface,
						SurfaceCompositeItem::posMode pm = SurfaceCompositeItem::center,
						Rect posFromCenterSurface = Rect());
	
	/**
	*	@brief Accesseur
	*	@return La hauteur de l'image
	*/
	virtual int h();
		
	/**
	*	@brief Accesseur
	*	@return La largeur de l'image
	*/
	virtual int w();
		
	virtual SurfaceCompositeItem *centerChild();
	
	/*!
	*	@brief Accesseur
	*	@return La liste des surfaces filles et de leurs positions relatives
	*	
	*	Les Surface ayant des enfants heritent de SurfaceComposite
	*/
	virtual std::vector<SurfaceCompositeItem *> *children () { return &m_children; }	
	
protected:
	std::vector<SurfaceCompositeItem *> m_children; 
private:
	
	
};



#endif
