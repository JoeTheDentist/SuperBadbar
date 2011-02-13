#ifndef _QCOLLISIONS_MATRIX_H
#define _QCOLLISIONS_MATRIX_H

#include <QGraphicsItem>           
#include <QString>


#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

class QGraphicsScene;
class MyGraphicsView;

struct CollItem {
	QGraphicsItem *item;
	int coll;
};

class QCollisionsMatrix {
	
	public:
	/*!
	*	@brief Constructeur
	*	@param width La largeur (en BOX) de la matrice de collisions
	*	@param height La hauteur (en BOX) de la matrice de collisions
	*/
	QCollisionsMatrix(int width, int height);
	
	/*!
	*	@brief Constructeur: charge la matrice dans un fichier
	*	@param fileName Le nom du fichier a ouvrir
	*/
	QCollisionsMatrix(QString fileName, MyGraphicsView *view);
	
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
	*	@brief 
	*/
	//TODO
	void setColl(int coll, int i, int j);
	void setItem(QGraphicsItem *item, int i, int j);
	bool constraintError(int i, int j);	
	
	//filename: *.coll
	void save(QString fileName);

	
	private:
	int m_width;
	int m_height;
	CollItem **m_coll_item;
	
};

#endif
