#ifndef _EDITOR_MY_GRAPHICS_VIEW_
#define _EDITOR_MY_GRAPHICS_VIEW_
#include <QGraphicsView>

#define CURS_BOX 0
#define CURS_LINE 1

#define BOX_SIZE 5

class QWidget;
class QGraphicsScene;
class QGraphicsItem;
class Data;


class MyGraphicsView : public QGraphicsView {
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene a afficher
	*	@param parent Le widget contenant le MyGraphicsView
	*/
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);
	
	/*!
	*	@brief Destructeur
	*/
	~MyGraphicsView();

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
	*	@brief 	Charge les donnees a partir du nom de fichier
	*	@param fileName Le nom du fichier (avec l'extension png)
	*	@param newFile Si vrai, un nouveau fichier col est crée, sinon un fichier .col est chargé
	*/
	void loadFile(QString fileName, bool newFile);

	/*!
	*	@brief 	Accesseur
	*	@return La largeur en pixels du niveau
	*/
	qreal xsize();
	
	/*!
	*	@brief 	Accesseur
	*	@return La hauteur en pixels du niveau
	*/
	qreal ysize();
	

	/*!
	*	@brief Sauvegarde de la matrice de collision dans le fichier str
	*	@param str Le chemin du fichier a sauvegarder (doit se terminer par .col)
	*/
	void save(QString str);


	private:
	Data *m_data;
	bool m_opened; // vaut vrai si un fichier est ouvert
	bool m_mouse_pressed;	// vaut vrai si un bouton de la souris est enfoncé
	qreal m_xsize; // largeur en pixel du niveau
	qreal m_ysize; // hauteur en pixel du niveau
	int m_xprec; // position x du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	int m_yprec; // position y du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
};

#endif
