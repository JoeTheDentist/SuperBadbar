#include "mainwindow.h"
#include "mygraphicsview.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsItem>

MainWindow::MainWindow()
{
	m_graphic_scene = new QGraphicsScene();
	m_graphic_view = new MyGraphicsView(m_graphic_scene, this);
	setCentralWidget(m_graphic_view);
	/* Temporaire */
	QGraphicsItem *item;
	QPixmap image;
	image.load("plop.png", 0, Qt::AutoColor);
	item = m_graphic_scene->addPixmap(image);
	/* ---------- */
	
//~ 	createActions();
//~ 	createMenus();
//~ 	createToolBars();
//~ 	createStatusBar();

//~ 	readSettings();

//~ 	connect(textEdit->document(), SIGNAL(contentsChanged()),
//~ 		this, SLOT(documentWasModified()));

//~ 	setCurrentFile("");
//~ 	setUnifiedTitleAndToolBarOnMac(true);
}
