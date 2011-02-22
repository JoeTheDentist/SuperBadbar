/**
 * 	@file collisions_matrix.h
 * 	@brief header de la classe Collisions_matrix
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _COLLISIONS_MATRIX_
#define _COLLISIONS_MATRIX_

#include <stdint.h>
#include <string>
#include "../util/globals.h"


/**
 * 	@class Collisions_matrix
 * 	@brief Classe gérant les collisions
//~  *
//~  *	Contient la matrice de collisions du niveau
//~  *	ainsi que les méthodes de collision utilisées dans le jeu
//~  *
//~  *	Une case de collision peut etre (simultanément):
//~  *	- bloquante par le bas
//~  *	- bloquante par le haut
//~  *	- bloquante par la droite
//~  *	- bloquante par la gauche
//~  *
//~  * Un nombre de collision caractérise la collision: on regarde les
//~  * 4 derniers bits: 1 signifie collision et 0 absence de collision
//~  * le bit de poids fort représente haut, puis bas, puis gauche, puis droite pour
//~  * le bit de poids faible
//~  *
//~  *	La classe fournit donc des méthodes pour
//~  *	déterminer la nature de la collision (is_xxxx_collision())
//~  *
//~  *	Pour savoir si un sprite peut avancer, on a besoin de connaitre la nature
//~  *	des cases de collision qui bordent ses extrémités (xxx_collision())
//~  *
//~
//~  *	@warning Beaucoup de vérifications sont faites pour éviter les dépassements de tableaux. On peut donc optimiser ici
 */
class Collisions_matrix {
protected:
	uint32_t ** m_collisions_matrix;      	/* matrice des statics */
	int m_collisions_matrix_w;
	int m_collisions_matrix_h;
public:

	Collisions_matrix();

	/*!
	 *	@brief Constructeur
	*/
	Collisions_matrix(std::string filename);

	/*!
	 *	@brief Destructeur
	*/
	virtual ~Collisions_matrix();


	/*!
	 *	@brief Retourne le type de collision de la matrice en un point
	 *	@param x Abscisse en pixels
	 *	@param y Ordonnée en pixels
	 *	@return Le type de collision en (x,y)
	*/
	uint32_t collision(uint32_t x, uint32_t y);

	/*!
	 *	@brief Calcule le type de collision des cases sous le rectangle
	 *	@param pos Rectangle à checker
	 *	@return Le type des collisions accumulées
	 *
	 * Dans la direction down, on vérifie qu'il n'y ait pas de dépassement de tableaux
	*/
	uint32_t down_collision_type(Rect pos);

	/*!
	 *	@brief Calcule le type de collision des cases au dessus du rectangle
	 *	@param pos Rectangle à checker
	 *	@return Le type des collisions accumulées
	*/
	uint32_t up_collision_type(Rect pos);

	/*!
	 *	@brief Calcule le type de collision des cases à gauche du rectangle
	 *	@param pos Rectangle à checker
	 *	@return Le type des collisions accumulées
	*/
	uint32_t left_collision_type(Rect pos);

	/*!
	 *	@brief Calcule le type de collision des cases à droite du rectangle
	 *	@param pos Rectangle à checker
	 *	@return Le type des collisions accumulées
	*/
	uint32_t right_collision_type(Rect pos);


	/*!
	 *	@brief Controle si un sprite peut monter
	 *	@param pos Rectangle du sprite à checker
	 *	@return Vrai si une case au dessus du rectangle est bloquante par le bas
	*/
	bool up_collision(Rect pos);

	/*!
	 *	@brief Controle si un sprite peut descendre
	 *	@param pos Rectangle du sprite à checker
	 *	@return Vrai si une case sous du rectangle est bloquante par le haut
	 */
	bool down_collision(Rect pos);

	/*!
	 *	@brief Controle si un sprite peut aller à gauche
	 *	@param pos Rectangle du sprite à checker
	 *	@return Vrai si une case à gauche du rectangle est bloquante par la droite
	*/
	bool left_collision(Rect pos);

	/*!
	 *	@brief Controle si un sprite peut aller à droite
	 *	@param pos Rectangle du sprite à checker
	 *	@return Vrai si une case à droite du rectangle est bloquante par la gauche
	 *	@todo verifier ce que fait cette méthode et ses analogues
	*/
	bool right_collision(Rect pos);

	/*!
	 * 	@brief Check les double_collision
	 * 	@return Vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle
	*/
	bool double_collision(Rect pos);

	/*!
	 * 	@brief Accesseur
	 * 	@return Dimension largeur
	*/
	int dim_w();

	/*!
	 * 	@brief Accesseur
	 * 	@return Dimension hauteur
	*/
	int dim_h();
};



#endif
