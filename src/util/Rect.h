/**
 * 	@file rect.h
 * 	@brief Header de la classe Rect
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 */

#ifndef _BABAR_RECT_H
#define _BABAR_RECT_H

/**
*	@class Rect
*	@brief Representation d'un rectangle (position et dimensions)
*
*	Note: cette classe possede des attributs publics et ne respecte pas le coding
*	style du m_ pour les attributs, afin d'acceder facilement aux champs x y h w
*/
class Rect {
public:
	int x;
	int y;
	int w;
	int h;

public:
	/**
	*	@brief Constructeur
	*	@param x_ Abcisse
	*	@param y_ Ordonnee
	*	@param w_ Largeur
	*	@param h_ Hauteur
	*/
	Rect(int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0);

	/**
	*	@brief Constructeur par copie
	*	@param rec L'objet a copier
	*/
	Rect(Rect const &rec);

	/**
	*	@brief Destructeur
	*/
	~Rect();

	/**
	*	@brief Accesseur
	*	@return La norme au carre
	*/
	int norm_2() const;

	/**
	*	@brief Determinant
	*	@param rect Le deuxieme vecteur du det
	*	@return Le determinant entre l'objet courant et rect
	*/
	int det(const Rect rect) const;

	/**
	*	@brief Operateur d'addition de deux rect
	*	@param rect2 Le deuxieme rect a additionner
	*	@return (*this) + rect2, en prenant les w et h de (*this)
	*/
	Rect operator+(const Rect &rect2) const;

	/**
	*	@brief Operateur de soustraction de deux rect
	*	@param rect2 Le deuxieme rect a soustraire
	*	@return (*this) - rect2, en prenant les w et h de (*this)
	*/
	Rect operator-(const Rect &rect2) const;

	/**
	*	@brief Operateur de produit scalaire de deux rect
	*	@param rect2 Le deuxieme rect
	*	@return (*this) * rect2, en prenant les w et h de (*this)
	*/
	int operator*(const Rect &rect2) const;
	
	/**
	*	@brief Operateur de produit par un scalaire
	*	@param coeff Le scalaire
	*	@return (*this) * coeff
	*
	*	Les champs h et w ne sont PAS affectes
	*/
	Rect operator*(int coeff) const;
	
	/**
	*	@brief Operateur de division par un scalaire
	*	@param coeff Le scalaire
	*	@return (*this) / coeff
	*
	*	Les champs h et w ne sont PAS affectes
	*/
	Rect operator/(int coeff) const;
	
};


#endif
