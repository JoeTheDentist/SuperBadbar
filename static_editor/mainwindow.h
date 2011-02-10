#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MyGraphicsView;

class MainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
	MainWindow();
	
	private:
	MyGraphicsView *m_graphic_view;
	QGraphicsScene *m_graphic_scene;
};




#endif
