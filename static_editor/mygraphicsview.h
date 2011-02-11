#ifndef _MY_GRAPHICS_VIEW_
#define _MY_GRAPHICS_VIEW_
#include <QGraphicsView>

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
	*	@brief Methode appelee quand l'utilisateur clique
	*	@param event L'event en question
	*/
	void mousePressEvent(QMouseEvent * event);
	
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

	
	private:
	QGraphicsItem *m_background; // image du static
	qreal m_xsize; // largeur en pixel de l'image du static
	qreal m_ysize; // hauteur en pixel de l'image du static
	int m_coll_width; // largeur en blocs de la matrice de collision
	int m_coll_height; // hauteur en blocs de la matrice de collision
	int **m_collision_matrix; // matrice de collision
	
	
};

#endif
