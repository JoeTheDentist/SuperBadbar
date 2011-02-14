#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

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
	*	@brief Charge un fichier .png
	*	@param str Nom du fichier (doit terminer par .png)
	*/
	void loadFile(QString str);
	
	/*!
	*	@brief Enregistre le .col en fonction des modifications faites
	*	@param str Nom au format .png du fichier à sauvegarder
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
	void aboutBabarStaticEditor();
	void setCursBox();
	void setCursLine();
	
	
	private:
	MyGraphicsView *m_graphic_view; // objet gérant 
	
	QGraphicsScene *m_graphic_scene;
	bool m_opened_file;
	QString m_file_name;
	
	QMenu *m_fileMenu;
	QMenu *m_editMenu;
	QMenu *m_helpMenu;
	QAction *m_newAct;
	QAction *m_openAct;
	QAction *m_exitAct;
	QAction *m_saveAct;
	QAction *m_aboutBabarStaticEditor;
	QAction *m_curs_box;
	QAction *m_curs_line;
	QToolBar *m_fileToolBar;



};


                 

#endif
