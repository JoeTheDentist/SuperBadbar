#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MyGraphicsView;
class QMenu;
class QAction;

class MainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
	MainWindow();
	void createActions();
	void createMenus();
	
	
	public slots:
	void aboutBabarStaticEditor();
	
	
	private:
	MyGraphicsView *m_graphic_view;
	QGraphicsScene *m_graphic_scene;
	
	QMenu *m_fileMenu;
	QAction *m_exitAct;
	
	QMenu *m_editMenu;
	
	QMenu *m_helpMenu;
	QAction *m_aboutBabarStaticEditor;


};


                 

#endif
