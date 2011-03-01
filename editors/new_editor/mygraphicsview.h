#ifndef _EDITOR_MY_GRAPHICS_VIEW_
#define _EDITOR_MY_GRAPHICS_VIEW_
#include <QGraphicsView>
#include "paths.h"
#include "babaritem.h"

#define CURS_BOX 0
#define CURS_LINE 1
#define BOX_SIZE 5

class QWidget;
class QGraphicsScene;
class QGraphicsPixmapItem;
class Data;
class MyItem;


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
	
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	
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
	*	@brief Traite l'événement wheel de la souris
	*	@param event L'event de la souris
	*/	
	virtual void wheelEvent(QWheelEvent *event);
	/*!
	*	@brief Traite l'appui sur une touche du clavier
	*	@param event L'event de la souris
	*/
	virtual void keyPressEvent(QKeyEvent *event);
 	/*!
	*	@brief Traite le relachement de la souris
	*	@param event L'event de la souris
	*/
	virtual void keyReleaseEvent(QKeyEvent *event);
	

	/*!
	*	@brief 	Charge les donnees a partir du nom de fichier
	*	@param backgroundName Un chemin absolu vers le fichier du fond d'écran
	*/
	void newFile( QString backgroundName);
	

	/*!
	*	@brief 	Charge les donnees a partir du nom de fichier
	*	@param fileName Le chemin relatif vers le fichier .lvl a ouvrir
	*/
	
	void loadFile(QString fileName);
	
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
	
	
	
	/*!
	*	@brief Fonction d'ajout de la position de babar
	*/
	void addBabar();

	
	
	/*!
	*	@brief Fonction d'ajout de static au niveau
	*/
	void addStatic();
	
	/*!
	*	@brief Fonction d'ajout de monstre au niveau
	*/
	void addMonster();
	
	
	/*!
	*	@brief Lance la possibilité de détruire un item au prochain clic
	*/
	void activeDeleteItem();
	
	/*!
	*	@brief Effectue un zoom sur le niveau de rapport z
	*	@param z Le rapport de zoom
	*/
	void zoom(qreal z);
	
	void selectItem(MyItem *item);
	void deSelectItem();
	void deleteFromEditor(MyItem *item);
	void copyItem(MyItem *item);
	void pastItem();


	private:
	Data *m_data;
	bool m_opened; // vaut vrai si un fichier est ouvert
	bool m_mouse_pressed;	// vaut vrai si un bouton de la souris est enfoncé
	bool m_ctrl_pressed; // vaut vrai quand la touche controle est pressee
	qreal m_xsize; // largeur en pixel du niveau
	qreal m_ysize; // hauteur en pixel du niveau
	int m_xprec; // position x du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	int m_yprec; // position y du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	BabarItem *m_babar_item; // l'item correspondant à la position actuelle de babar
	MyItem *m_curr_item; // l'item en cours d'ajout
	MyItem *m_selected_item; // l'item selectionne
	MyItem *m_moved_item; // l'item selectionne (pour un deplacement)
	MyItem *m_copied_item;
	QGraphicsPixmapItem *m_del_curs; // l'image au bout du curseur quand on veut supprimer un item
	qreal m_zoom; // le niveau de zoom actuel
	QGraphicsItem *m_background;
};

#endif
