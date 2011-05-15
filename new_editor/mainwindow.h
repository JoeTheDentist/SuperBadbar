#ifndef _EDITOR_MAIN_WINDOW_H
#define _EDITOR_MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MyGraphicsView;
class QMenu;
class QAction;
class QToolBar;

/*!
*	@class MainWindow
*	@brief Gestion de la fenetre principale de l'editeur
*/
class MainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
	/*!
	*	@brief Constructeur
	*/
	MainWindow();
	
	/*!
	*	@brief Destructeur
	*/
	~MainWindow();
	
	private:
	/*!
	*	@brief Initialisation des actions
	*/
	void createActions();
	
	/*!
	*	@brief Initialisation des menus
	*/
	void createMenus();
	
	/*!
	*	@brief Initialisation de la toolbar
	*/
	void createToolBars();
	

	/*!
	*	@brief Enregistre le niveau en fonction des modifications faites
	*	@param str Nom (terminant par .lvl) du fichier à sauvegarder
	*/
	void saveFile(QString str);

	/*!
	*	@brief Demande a l'utilisateur s'il veut sauvegarder son travail
	*/
	void warningSave();
	
	
	public slots:
	void newFile();
	void open();
	void save();
	void saveAs();
	void aboutBabarEditor();
	void createNewBabar();
	void createNewSet();
	void createNewStatic();
	void addMovingPlatform();
	void addFallingPlatform();
	void createNewMonster();
	void createNewEvent();
	void createNewTrigger();
	void deleteItem();
	
	
	private:
	QGraphicsScene *m_graphic_scene; // scene liee a m_graphic_view
	MyGraphicsView *m_graphic_view; // objet principal de l'éditeur
	bool m_opened_file; // vaut vrai si un fichier est ouvert, faux sinon
	QString m_file_name; // le nom du fichier en cours (si un fichier est ouvert)
	
	// variables du menu
	QMenu *m_fileMenu;
	QMenu *m_editMenu;
	QMenu *m_helpMenu;
	// actions possibles
	QAction *m_newAct;
	QAction *m_openAct;
	QAction *m_exitAct;
	QAction *m_saveAct;
	QAction *m_saveAsAct;
	QAction *m_aboutBabarEditor;
	QAction *m_createNewBabar;
	QAction *m_createNewSet;
	QAction *m_createNewStatic;
	QAction *m_addMovingPlatform;
	QAction *m_addFallingPlatform;
	QAction *m_createNewMonster;
	QAction *m_createNewEvent;
	QAction *m_createNewTrigger;
	QAction *m_deleteItem;
	//barre d'outils
	QToolBar *m_fileToolBar;
};


                 

#endif
