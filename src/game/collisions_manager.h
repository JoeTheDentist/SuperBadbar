/**
 * 	@file collisions_manager.h
 * 	@brief header de la classe Collisions_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _COLLISIONS_MANAGER_
#define _COLLISIONS_MANAGER_

#include <stdint.h>
#include "../util/globals.h"
#include "../util/lists.h"

class Static;


/**
 * 	@class Collisions_manager
 * 	@brief Classe gérant les collisions
 *
 *	Contient la matrice de collisions du niveau
 *	ainsi que les méthodes de collision utilisées dans le jeu
 *
 *	Une case de collision peut etre (simultanément):
 *	- bloquante par le bas
 *	- bloquante par le haut
 *	- bloquante par la droite
 *	- bloquante par la gauche
 *
 *	La classe fournit donc des méthodes pour
 *	déterminer la nature de la collision (is_xxxx_collision())
 * 
 *	Pour savoir si un sprite peut avancer, on a besoin de connaitre la nature
 *	des cases de collision qui bordent ses extrémités (xxx_collision())
 *
 
 *	@warning Beaucoup de vérifications sont faites pour éviter les dépassements de tableaux. On peut donc optimiser ici
 *	@todo Ajouter les méthodes de collisions.h en static dans cette classe	
 */
class Collisions_manager {
private:
	uint32_t ** m_collisions_matrix;      	/* matrice des statics */
	uint32_t m_collisions_matrix_w;
	uint32_t m_collisions_matrix_h;

public:
	
	/*!
	 *	@brief Constructeur
	*/
	Collisions_manager();
	
	/*!
	 *	@brief Destructeur
	*/
	~Collisions_manager();

	/*!
	 *	@brief Initialisation de la matrice de collision
	 *	@param level Le numéro du niveau à charger
	*/
	void init_collisions_manager(int level);

	/*!
	 *	@brief Controle la collision de deux rectangles
	 * 	@param A Premier rectangle
	 *	@param B Deuxieme rectangle
	 *	@return Vrai si les deux rectangles sont en collision
	*/
	static bool check_collision(Rect A, Rect B);

	/*!
	 *	@brief Retourne le type de collision du niveau en un point
	 *	@param x Abscisse en pixels
	 *	@param y Ordonnée en pixels
	 *	@return Le type de collision en (x,y)
	*/
	uint32_t collision(uint32_t x, uint32_t y);
	
	/*!
	 *	@brief Calcule le type de collision des cases sous le rectangle
	 *	@param pos Rectangle à checker
	 *	@return Le type des collisions accumulées
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
	*/	
	bool right_collision(Rect pos);

	/*!
	 * 	@brief Check les double_collision 
	 * 	@return Vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle 
	 *	@todo verifier la fonction et ce qu'elle doit faire
	*/
	bool double_collision(Rect pos);

};



#endif
