#ifndef _MY_GRAPHICS_VIEW_
#define _MY_GRAPHICS_VIEW_
#include <QGraphicsView>
#include "qcollisions_matrix.h"

#define BOX_SIZE 5

class QWidget;
class QGraphicsScene;
class QGraphicsItem;



class MyGraphicsView : public QGraphicsView {
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene a afficher
	*	@param parent Le widget contenant le MyGraphicsView
	*/
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);

	//TODO
	int posClicX(QMouseEvent *event);	
	//TODO
	int posClicY(QMouseEvent *event);	
	
	/*!
	*	@brief Methode appelee quand l'utilisateur clique
	*	@param event L'event en question
	*/
	virtual void mousePressEvent(QMouseEvent * event);
	
	//TODO
	virtual void mouseReleaseEvent(QMouseEvent * event);
	
	
	//TODO
	virtual void mouseMoveEvent(QMouseEvent *event);
	
	//TODO
	void setBox(int coll, int x, int y);
	
	/*!
	*	@brief 	Charge les donnees a partir du nom de fichier
	*	@param fileName Le nom du fichier (avec l'extension png)
	*/
	void loadFile(QString fileName);
	
	/*!
	*	@brief 	Charge les donnees de collision a partir du nom de fichier
	*	Si le fichier est vide, une nouvelle matrice de collision est cree
	*/
	void loadCol(QString fileName);
	
	/*!
	*	@brief 	Accesseur
	*	@return La largeur en pixel de l'image du static
	*/
	qreal xsize();
	
	/*!
	*	@brief 	Accesseur
	*	@return La hauteur en pixel de l'image du static
	*/
	qreal ysize();
	
	//TODO
	void setCurrentColl(int coll);

	void save(QString str);

	void refreshScene();
	
	private:
	bool m_opened;
	bool m_mouse_pressed;
	QGraphicsItem *m_background; // image du static
	qreal m_xsize; // largeur en pixel de l'image du static
	qreal m_ysize; // hauteur en pixel de l'image du static
	int m_coll_width; // largeur en blocs de la matrice de collision
	int m_coll_height; // hauteur en blocs de la matrice de collision
	QCollisionsMatrix *m_collisions_matrix; // matrice de collision
	QPixmap m_full_pic;
	QPixmap m_down_pic;
	int m_coll_curs;

	
	
};

#endif
