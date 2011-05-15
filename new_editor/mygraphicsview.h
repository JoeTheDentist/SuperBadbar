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
class QGraphicsSimpleTextItem;
class QStatusBar;
class Data;
class MyItem;
class MainWindow;

enum mgvState {
	e_fileClosed, e_addingItem, e_movingItem, e_erasingItem, e_none
};


class MyGraphicsView : public QGraphicsView {

	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene a afficher
	*	@param parent Le widget contenant le MyGraphicsView
	*/
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent, MainWindow *mainWindow);
	
	/*!
	*	@brief Destructeur
	*/
	~MyGraphicsView();

	/*!
	*	@brief Donne au mygraphicsview une barre de status 
	*	@param status La barre de status
	*/
	void setStatusBar(QStatusBar *statusBar) {m_statusBar = statusBar;}
	

	
	
	/*!
	*	@brief Calcule l'abscisse du clic par rapport a la scene
	*	@param event L'evenement de la souris
	*	@return L'abscisse entiere
	*/
	int posClicX(QMouseEvent *event);
	
	/*!
	*	@brief Calcule l'ordonnee du clic par rapport a la scene
	*	@param event L'evenement de la souris
	*	@return L'ordonnee entiere
	*/
	int posClicY(QMouseEvent *event);	
	
	/*!
	*	@brief Traite le clic de la souris
	*	@param event L'event de la souris
	*/
	virtual void mousePressEvent(QMouseEvent * event);
	
	/*!
	*	@brief Traite le double clic de la souris
	*	@param event L'event de la souris
	*/	
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
	void createNewBabar();
	
	/*!
	*	@brief Fonction d'ajout de set (decor) au niveau
	*/
	void createNewSet();	
	
	/*!
	*	@brief Fonction d'ajout de static au niveau
	*/
	void createNewStatic();		
	
	/*!
	*	@brief Fonction d'ajout de static au niveau
	*/
	void addMovingPlatform();	
	
	/*!
	*	@brief Fonction d'ajout de static au niveau
	*/
	void addFallingPlatform();
	
	/*!
	*	@brief Fonction d'ajout de monstre au niveau
	*/
	void createNewMonster();
	
	/*!
	*	@brief Fonction d'ajout d'un event au niveau
	*/
	void createNewEvent();
	
	/*!
	*	@brief Fonction d'ajout d'un Trigger au niveau
	*/
	void createNewTrigger();
	
	
//~ 	void addItem(MyItem *item);

	
	/*!
	*	@brief Lance la possibilité de détruire un item au prochain clic
	*/
	void activeDeleteItem();
	
	
	/*!
	*	@brief Met l'etat a e_addingItem sur l'item specifie
	*	@param item l'item a ajouter
	*/
	void setStateAddingItem(MyItem *item);
	void setStateMovingItem() {m_state = e_movingItem;}
	void setStateErasingItem() {m_state = e_erasingItem;}
	/*!
	*	@brief Met l'etat a e_none
	*/
	void setStateNone() {m_state = e_none;}
	
	
	/*!
	*	@brief Effectue un zoom sur le niveau de rapport z
	*	@param z Le rapport de zoom
	*/
	void zoom(qreal z);
	
	MainWindow *getWindow() {return m_main_window;}
	
	Data *getData() {return m_data;}
	
	bool fileOpened() const {return m_state != e_fileClosed;}

	
	void selectItem(MyItem *item);
	void deSelectItem();
	void deleteFromEditor(MyItem *item);
	void copyItem(MyItem *item);
	void pastItem();


	private:
	mgvState m_state;
	MainWindow *m_main_window;
	QString m_file_name;
	Data *m_data; // Toute les donnees a sauvegarder y sont stockees
	bool m_mouse_pressed;	// vaut vrai si un bouton de la souris est enfoncé
	bool m_ctrl_pressed; // vaut vrai quand la touche controle est pressee
	qreal m_xsize; // largeur en pixel du niveau
	qreal m_ysize; // hauteur en pixel du niveau
	int m_xprec; // position x du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	int m_yprec; // position y du dernier mouvement de souris (utile pour tracer en cliquer-glisser)
	BabarItem *m_babar_item; // l'item correspondant à la position actuelle de babar
	MyItem *m_item_being_added; // l'item en cours d'ajout
	MyItem *m_selected_item; // l'item selectionne
	MyItem *m_moved_item; // l'item selectionne (pour un deplacement)
	MyItem *m_copied_item;
	QGraphicsPixmapItem *m_del_curs; // l'image au bout du curseur quand on veut supprimer un item
	qreal m_zoom; // le niveau de zoom actuel
	QGraphicsItem *m_background; // Le fond d'écran
	QStatusBar *m_statusBar; // Pointeur vers la statusBar de mainwindow (a ne pas delete ici!!)
};

#endif
