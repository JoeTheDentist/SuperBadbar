#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MyGraphicsView;
class QMenu;
class QAction;
class QToolBar;

class MainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
	MainWindow();
	
	private:
	void createActions();
	void createMenus();
	void createToolBars();
	void loadFile(QString str);
	void saveFile(QString str);

	
	
	public slots:
	void newFile();
	void open();
	void aboutBabarStaticEditor();
	
	
	private:
	MyGraphicsView *m_graphic_view;
	QGraphicsScene *m_graphic_scene;
	bool m_opened_file;
	QString m_file_name;
	
	QMenu *m_fileMenu;
	QAction *m_newAct;
	QAction *m_openAct;
	QAction *m_exitAct;
	
	QMenu *m_editMenu;
	
	QMenu *m_helpMenu;
	QAction *m_aboutBabarStaticEditor;
	
	QToolBar *m_fileToolBar;



};


                 

#endif
