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
#include <QFileDialog>
#include <QToolBar>
#include <QScrollBar>

MainWindow::MainWindow()
{
	m_graphic_scene = new QGraphicsScene();
	m_graphic_view = new MyGraphicsView(m_graphic_scene, this);
	setCentralWidget(m_graphic_view);
	m_opened_file = false;
	
	createActions();
	createMenus();
	createToolBars();
//~ 	createStatusBar();

//~ 	readSettings();

//~ 	connect(textEdit->document(), SIGNAL(contentsChanged()),
//~ 		this, SLOT(documentWasModified()));

//~ 	setCurrentFile("");
	setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::createActions()
{

	m_newAct = new QAction(QIcon("images/new.png"), tr("&New"), this);
	m_newAct->setShortcuts(QKeySequence::New);
	m_newAct->setStatusTip(tr("Create a new file"));
	connect(m_newAct, SIGNAL(triggered()), this, SLOT(newFile()));
	
	m_openAct = new QAction(QIcon("images/open.png"), tr("&Open..."), this);
	m_openAct->setShortcuts(QKeySequence::Open);
	m_openAct->setStatusTip(tr("Open an existing file"));
	connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));
	
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
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
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

void MainWindow::createToolBars()
{
	m_fileToolBar = addToolBar(tr("File"));
	m_fileToolBar->addAction(m_newAct);
	m_fileToolBar->addAction(m_openAct);
//~ 	m_fileToolBar->addAction(m_saveAct);

//~ 	editToolBar = addToolBar(tr("Edit"));
//~ 	editToolBar->addAction(cutAct);
//~ 	editToolBar->addAction(copyAct);
//~ 	editToolBar->addAction(pasteAct);	
}


void MainWindow::newFile()
{
	
}

void MainWindow::open()
{
	if (m_opened_file) {
		QMessageBox mb(	"Static Editor", "Saving the file will overwrite the original file on the disk.\n",
		QMessageBox::Information,
		QMessageBox::Cancel | QMessageBox::Escape,
		QMessageBox::No,
		QMessageBox::Yes | QMessageBox::Default);
		mb.setButtonText(QMessageBox::Yes, "Save");
		mb.setButtonText(QMessageBox::No, "Discard");
		switch(mb.exec()) {
		case QMessageBox::Yes:
			saveFile(m_file_name);
			break;
		case QMessageBox::No:
			break;
		case QMessageBox::Cancel:
			return;
		}
	}
	QString fileName = QFileDialog::getOpenFileName(this);
	if (fileName.isEmpty()) {
		return;
	}
	if (!fileName.endsWith(".png")) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".pgn\"");
		return;
	}
	m_opened_file = true;
	loadFile(fileName);
}

void MainWindow::saveFile(QString str)
{
	std::cout << "sauvegarde" << std::endl;	
}

void MainWindow::loadFile(QString str)
{
	m_file_name = str;
	m_graphic_view->loadFile(str);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
}

void MainWindow::aboutBabarStaticEditor()
{
	QMessageBox::information(this, "About us", "Babar Static Editor is a Qt tool for editing SuperBabar static objects. Read the manual for more informations. You can also visit our website: <a href=\"http://nalwarful.free.fr/Babar/jeu.php\"> SuperBabar </a>");

}
