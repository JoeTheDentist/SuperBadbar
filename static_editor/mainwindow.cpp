#include "mainwindow.h"
#include "mygraphicsview.h"
#include <iostream>
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow()
{
	m_graphic_scene = new QGraphicsScene();
	m_graphic_view = new MyGraphicsView(m_graphic_scene, this);
	setCentralWidget(m_graphic_view);

	
	createActions();
	createMenus();
//~ 	createToolBars();
//~ 	createStatusBar();

//~ 	readSettings();

//~ 	connect(textEdit->document(), SIGNAL(contentsChanged()),
//~ 		this, SLOT(documentWasModified()));

//~ 	setCurrentFile("");
	setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::createActions()
{
	m_exitAct = new QAction(tr("E&xit"), this);
	m_exitAct->setShortcuts(QKeySequence::Quit);
	m_exitAct->setStatusTip(tr("Exit the application"));
	connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));	
	
	m_aboutBabarStaticEditor = new QAction(tr("About"), this);
	m_aboutBabarStaticEditor->setStatusTip(tr("About Babar Static Editor"));
	connect(m_aboutBabarStaticEditor, SIGNAL(triggered()), this, SLOT(aboutBabarStaticEditor()));
}

 void MainWindow::createMenus()
 {
	m_fileMenu = menuBar()->addMenu(tr("&File"));
//~      fileMenu->addAction(newAct);
//~      fileMenu->addAction(openAct);
//~      fileMenu->addAction(saveAct);
//~      fileMenu->addAction(saveAsAct);
//~      fileMenu->addSeparator();
	m_fileMenu->addAction(m_exitAct);

	m_editMenu = menuBar()->addMenu(tr("&Edit"));
//~      editMenu->addAction(cutAct);
//~      editMenu->addAction(copyAct);
//~      editMenu->addAction(pasteAct);

	menuBar()->addSeparator();

	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutBabarStaticEditor);
//~      helpMenu->addAction(aboutQtAct);
}


void MainWindow::aboutBabarStaticEditor()
{
	std::cout << "ABOUT" << std::endl;
	QMessageBox::information(this, "About us", "Babar Static Editor is a Qt tool for editing SuperBabar static objects. Read the manual for more informations. You can also visit our website: <a href=\"http://nalwarful.free.fr/Babar/jeu.php\"> SuperBabar </a>");



}
