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

	setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

	delete m_newAct;
	delete m_openAct;
	delete m_exitAct;
	delete m_saveAct;
	delete m_aboutBabarEditor;
	delete m_fileMenu;
	delete m_editMenu;
	delete m_helpMenu;
	delete m_graphic_scene;
	delete m_graphic_view;

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
	
	m_aboutBabarEditor = new QAction(tr("About"), this);
	m_aboutBabarEditor->setStatusTip(tr("About Babar Editor"));
	connect(m_aboutBabarEditor, SIGNAL(triggered()), this, SLOT(aboutBabarEditor()));
	
	m_saveAct = new QAction(QIcon("images/save.png"),tr("Save"), this);
	m_saveAct->setShortcuts(QKeySequence::Save);
	m_saveAct->setStatusTip(tr("Save the .col file"));
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));	
}

 void MainWindow::createMenus()
 {
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
	m_fileMenu->addAction(m_saveAct);
	m_fileMenu->addAction(m_exitAct);
	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	menuBar()->addSeparator();
	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutBabarEditor);
}

void MainWindow::createToolBars()
{
	m_fileToolBar = addToolBar(tr("File"));
	m_fileToolBar->addAction(m_newAct);
	m_fileToolBar->addAction(m_openAct);
	m_fileToolBar->addAction(m_saveAct);
}

void MainWindow::newFile()
{
	if (m_opened_file) {
		warningSave();
	}
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier .png");
	if (fileName.isEmpty()) {
		return;
	}
	if (!fileName.endsWith(".png")) {
		QMessageBox::critical(this, "File opening", "filename must ends with \".pgn\"");
		return;
	}
	m_opened_file = true;
	m_file_name = fileName;
	m_graphic_view->loadFile(fileName, true);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
}

void MainWindow::open()
{
	if (m_opened_file) {
		warningSave();
	}
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier .png");
	if (fileName.isEmpty()) {
		return;
	}
	if (!fileName.endsWith(".png")) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".pgn\"");
		return;
	}
	m_opened_file = true;
	m_file_name = fileName;
	m_graphic_view->loadFile(fileName, false);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
}

void MainWindow::save()
{
	if (m_opened_file)
		this->saveFile(m_file_name);
}

void MainWindow::saveFile(QString str)
{
	std::cout << "sauvegarde" << std::endl;
	str.chop(3);
	str.append("col");
	m_graphic_view->save(str);
}

void MainWindow::loadFile(QString str)
{
	m_file_name = str;
	m_graphic_view->loadFile(str, false);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
}

void MainWindow::aboutBabarEditor()
{
	QMessageBox::information(this, "About us", "Babar Editor is a graphic editor using Qt to design SuperBabar levels. \
		Read the manual for more informations. You can also visit our website: \
		<a href=\"http://nalwarful.free.fr/Babar/jeu.php\"> SuperBabar </a>");
}

void MainWindow::warningSave()
{
	QMessageBox mb(	"Editor", "Saving the file will overwrite the original file on the disk.\n",
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
