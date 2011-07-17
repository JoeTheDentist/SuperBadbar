/**
 * 	@file CollisionsMatrix.h
 * 	@brief header de la classe CollisionsMatrix
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _COLLISIONS_MATRIX_
#define _COLLISIONS_MATRIX_

#include <stdint.h>
#include <string>
#include "../util/debug.h"


/**
 * 	@class CollisionsMatrix
 * 	@brief Classe g√©rant les collisions
//~  *
//~  *	Contient la matrice de collisions du niveau
//~  *	ainsi que les m√©thodes de collision utilis√©es dans le jeu
//~  *
//~  *	Une case de collision peut etre (simultan√©ment):
//~  *	- bloquante par le bas
//~  *	- bloquante par le haut
//~  *	- bloquante par la droite
//~  *	- bloquante par la gauche
//~  *
//~  * Un nombre de collision caract√©rise la collision: on regarde les
//~  * 4 derniers bits: 1 signifie collision et 0 absence de collision
//~  * le bit de poids fort repr√©sente haut, puis bas, puis gauche, puis droite pour
//~  * le bit de poids faible
//~  *
//~  *	La classe fournit donc des m√©thodes pour
//~  *	d√©terminer la nature de la collision (is_xxxx_collision())
//~  *
//~  *	Pour savoir si un sprite peut avancer, on a besoin de connaitre la nature
//~  *	des cases de collision qui bordent ses extr√©mit√©s (xxx_collision())
//~  *
//~
//~  *	@warning Beaucoup de v√©rifications sont faites pour √©viter les d√©passements de tableaux. On peut donc optimiser ici
 */

struct Rect;
class Camera;

class CollisionsMatrix {
protected:
	unsigned int ** m_collisions_matrix;      	/* matrice des statics */
	int m_collisions_matrix_w; // taille de la matrice (en box)
	int m_collisions_matrix_h;
public:

	/**
	 *	@brief Constructeur par defaut
	*/
	CollisionsMatrix();

	/**
	 *	@brief Constructeur
	 *	@param w La largeur de la matrice en BOX
	 *	@param h La hauteur de la matrice en BOX
	*/
	CollisionsMatrix(int w, int h);

	/**
	 *	@brief Destructeur
	*/
	virtual ~CollisionsMatrix();

	//static_name: le nom du static depuis le dossier des statics sans l'extension
	// x et y les positions en pixels
	/**
	 *	@brief Ajoute les collisions du static a la matrice
	 *	@param x L'abscisse en pixels du static a ajouter
	 *	@param y L'ordonnee en pixels du static a ajouter
	 *	@param varCol La valeur de la collision variable du static a ajouter
	 *	@param static_name Le nom du static (depuis le dossier des statics et sans l'extension)
	 */
	void addStatic(int x, int y, int varCol, std::string static_name);

	/**
	 *	@brief Retourne le type de collision de la matrice en un point
	 *	@param x Abscisse en pixels
	 *	@param y Ordonn√©e en pixels
	 *	@return Le type de collision en (x,y)
	*/
	unsigned int collision(unsigned int x, unsigned int y);

	/**
	 *	@brief Calcule le type de collision des cases sous le rectangle
	 *	@param pos Rectangle √  checker
	 *	@return Le type des collisions accumul√©es
	 *
	 * Dans la direction down, on v√©rifie qu'il n'y ait pas de d√©passement de tableaux
	*/
	unsigned int down_collision_type(Rect pos);

	/**
	 *	@brief Calcule le type de collision des cases au dessus du rectangle
	 *	@param pos Rectangle √  checker
	 *	@return Le type des collisions accumul√©es
	*/
	unsigned int up_collision_type(Rect pos);

	/**
	 *	@brief Calcule le type de collision des cases √  gauche du rectangle
	 *	@param pos Rectangle √  checker
	 *	@return Le type des collisions accumul√©es
	*/
	unsigned int left_collision_type(Rect pos);

	/**
	 *	@brief Calcule le type de collision des cases √  droite du rectangle
	 *	@param pos Rectangle √  checker
	 *	@return Le type des collisions accumul√©es
	*/
	unsigned int right_collision_type(Rect pos);


	/**
	 *	@brief Controle si un sprite peut monter
	 *	@param pos Rectangle du sprite √  checker
	 *	@return Vrai si une case au dessus du rectangle est bloquante par le bas
	*/
	bool up_collision(Rect pos);

	/**
	 *	@brief Controle si un sprite peut descendre
	 *	@param pos Rectangle du sprite √  checker
	 *	@return Vrai si une case sous du rectangle est bloquante par le haut
	 */
	bool down_collision(Rect pos);

	/**
	 *	@brief Controle si un sprite peut aller √  gauche
	 *	@param pos Rectangle du sprite √  checker
	 *	@return Vrai si une case √  gauche du rectangle est bloquante par la droite
	*/
	bool left_collision(Rect pos);

	/**
	 *	@brief Controle si un sprite peut aller √  droite
	 *	@param pos Rectangle du sprite √  checker
	 *	@return Vrai si une case √  droite du rectangle est bloquante par la gauche
	 *	@todo verifier ce que fait cette m√©thode et ses analogues
	*/
	bool right_collision(Rect pos);

	/**
	 * 	@brief Check les double_collision
	 * 	@return Vrai si deux cases de collisions ou une case de collision bas sont sous le rectangle
	*/
	bool double_collision(Rect pos);

	/**
	 * 	@brief Accesseur
	 * 	@return Dimension largeur
	*/
	int dim_w();

	/**
	 * 	@brief Accesseur
	 * 	@return Dimension hauteur
	*/
	int dim_h();

	/**
	 * 	@brief Regarde si la position est succeptible de tomber
	 * 	@return l'assertion
	*/
	bool can_fall(Rect pos);

//~ 	virtual Rect position();

	#ifdef DEBUG_COLL
	void display_coll(Camera *camera);
	#endif

	void update_pos( Rect &pos, Rect &speed );
};



#endif
