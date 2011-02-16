#ifndef _MY_GRAPHICS_VIEW_
#define _MY_GRAPHICS_VIEW_
#include <QGraphicsView>
#include "qcollisions_matrix.h"
#include "histo.h"

#define CURS_BOX 0
#define CURS_LINE 1

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

	/*!
	*	@brief Calcule l'abscisse du clic par rapport a la scene
	*	@param event L'evenement de la souris
	*	@return L'abscisse entiere
	*/
	int posClicX(QMouseEvent *event);
	

	/*!
	*	@brief Calcule l'abscisse du clic par rapport a la scene
	*	@param event L'evenement de la souris
	*	@return L'abscisse entiere
	*/
	int posClicY(QMouseEvent *event);	
	
	/*!
	*	@brief Traite le clic de la souris
	*	@param event L'event de la souris
	*/
	virtual void mousePressEvent(QMouseEvent * event);
	
	/*!
	*	@brief Traite le relachement de la souris
	*	@param event L'event de la souris
	*/
	virtual void mouseReleaseEvent(QMouseEvent * event);
	
	
	/*!
	*	@brief Traite le deplacement de la souris
	*	@param event L'event de la souris
	*/
	virtual void mouseMoveEvent(QMouseEvent *event);
	
	/*!
	*	@brief Met à jour un carré la matrice de collision
	*	@param coll La nouvelle collision
	*	@param x La position x du clic en pixels
	*	@param y La position y du clic en pixels
	*/
	void setBox(int coll, int x, int y, bool save = true);
	
	/*!
	*	@brief 	Charge les donnees a partir du nom de fichier
	*	@param fileName Le nom du fichier (avec l'extension png)
	*	@param newFile Si vrai, un nouveau fichier col est crée, sinon un fichier .col est chargé
	*/
	void loadFile(QString fileName, bool newFile);

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
	
	/*!
	*	@brief Modifie la collision ("couleur") active du curseur
	*	@param coll La nouvelle collision
	*/
	void setCurrentColl(int coll);

	/*!
	*	@brief Sauvegarde de la matrice de collision dans le fichier str
	*	@param str Le chemin du fichier a sauvegarder (doit se terminer par .col)
	*/
	void save(QString str);
	
	//TODO
	void draw_line(int coll, float x, float y, float X, float Y);


	/*!
	*	TODO
	*/
	void refreshScene();
	
	//TODO
	void setCursorShape(int shape);
	
	void setCursorCol(int col);
	
	void undo();
	
	private:
	bool m_opened; // vaut vrai si un fichier est ouvert
	bool m_mouse_pressed;	// vaut vrai si un bouton de la souris est enfoncé
	QGraphicsItem *m_background; // image du static
	qreal m_xsize; // largeur en pixel de l'image du static
	qreal m_ysize; // hauteur en pixel de l'image du static
	int m_coll_width; // largeur en blocs de la matrice de collision
	int m_coll_height; // hauteur en blocs de la matrice de collision
	QCollisionsMatrix *m_collisions_matrix; // matrice de collision
	QPixmap m_full_pic; // image d'une collision pleine (carre rouge)
	QPixmap m_down_pic; // image d'une collision par le bas (carre vert)
	int m_coll_curs; // collision courante (celle qui sera ajoute a chaque clic)
	int m_xprec; // position x du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	int m_yprec; // position y du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	int m_curs_shape; // forme du curseur (point, ligne...)
	Histo m_histo; // historique pour le undo
};

#endif
