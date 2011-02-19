#ifndef _QCOLLISIONS_MATRIX_H
#define _QCOLLISIONS_MATRIX_H

#include <QString>

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

class QGraphicsItem;
class QGraphicsScene;

struct CollItem;

class QCollisionsMatrix {
	
	public:
	/*!
	*	@brief Constructeur
	*	@param width La largeur (en BOX) de la matrice de collisions
	*	@param height La hauteur (en BOX) de la matrice de collisions
	*/
	QCollisionsMatrix(int width, int height);
	
	
	/*!
	*	@brief Destructeur
	*/
	~QCollisionsMatrix();
	
	/*!
	*	@brief Accesseur sur la largeur en BOX de la matrice
	*	@return La largeur en BOX de la matrice
	*/
	int width();

	/*!
	*	@brief Accesseur sur la hauteur en BOX de la matrice
	*	@return La hauteur en BOX de la matrice
	*/
	int height();

	/*!
	*	@brief Accesseur sur la collision en (i,j)
	*	@param i Abcisse (en BOX) de la case voulue
	*	@param j Ordonnee (en BOX) de la case voulue
	*/
	int coll(int i, int j);
	
	/*!
	*	@brief Accesseur sur l'item (contenant une image) en (i,j)
	*	@param i Abcisse (en BOX) de la case voulue
	*	@param j Ordonnee (en BOX) de la case voulue
	*/	
	QGraphicsItem *item(int i, int j);
	
	/*!
	*	@brief Mutateur d'une case de collision
	*	@param coll La nouvelle collision
	*	@param i L'abscisse (en BOX) de la case à changer
	*	@param j L'ordonnee (en BOX) de la case à changer
	*/
	void setColl(int coll, int i, int j);

 	/*!
	*	@brief Mutateur d'une case d'item
	*	@param item Le nouvel item
	*	@param i L'abscisse (en BOX) de la case à changer
	*	@param j L'ordonnee (en BOX) de la case à changer
	*/
	void setItem(QGraphicsItem *item, int i, int j);
	bool constraintError(int i, int j);	
	
	
	/*!
	*	@brief Sauvegarde la matrice dans un fichier
	*	@param fileName Le nom du fichier terminant par .coll
	*/
	void save(QString fileName);

	
	private:
	int m_width; // largeur en BOX (pixels/BOX_SIZE) de la matrice
	int m_height; // hauteur en BOX (pixels/BOX_SIZE) de la matrice
	CollItem **m_coll_item; // Matrice des collisions et des items
	
};

#endif
