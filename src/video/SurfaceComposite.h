
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
#include "video/Surface.h"

/*!
*	@class SurfaceComposite
*	@brief Une surface contenant d'autres surfaces
*
*	La surface contient une surface dite centrale puis d'autres
*	surfaces pouvant etre positionnees par rapport a cette surface
*
*	@todo commenter mieux
*/
class SurfaceComposite: public Surface
{
public:


    /*!
    *	@brief Constructeur
    *	@param center La surface centrale
    */
    SurfaceComposite (Surface *center);

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
    *	@return L'indice de l'enfant dans le tableau
    */
    int addChild (	Surface *surface,
                    SurfaceCompositeItem::posMode pm = SurfaceCompositeItem::center,
                    Rect posFromCenterSurface = Rect() );

    /*!
    *	@brief Change la surface contenue a l'indice i
    *	@param i L'indice
    *	@param surface La nouvelle surface
    *
    *	Si l'indice est invalide, ne fait rien
    */
    void setSurface (unsigned int i, Surface *surface);

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


    /**
    *	@brief Accesseur
    *	@return La surface centrale
    */
    virtual SurfaceCompositeItem *centerChild() const;

    /*!
    *	@brief Accesseur
    *	@return La liste des surfaces filles et de leurs positions relatives
    *
    *	Les Surface ayant des enfants heritent de SurfaceComposite
    */
    virtual std::vector<SurfaceCompositeItem *> *children ()
    {
        return &m_children;
    }

    /*!
    *	@brief Accesseur
    *	@return La position de la surface centrale PAR RAPPORT AU COIN DE LA SURFACE COMPOSITE
    */
    virtual Rect centerChildPos() const;

    virtual int centerWidth() const;
    virtual int centerHeight() const;

protected:
    std::vector<SurfaceCompositeItem *> m_children; // le parent doit etre le premier
private:


};



#endif
