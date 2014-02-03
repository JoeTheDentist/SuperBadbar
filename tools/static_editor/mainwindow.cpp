#include "mainwindow.h"
#include "mygraphicsview.h"
#include "directories.h"
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

MainWindow::~MainWindow()
{

	delete m_newAct;
	delete m_openAct;
	delete m_exitAct;
	delete m_saveAct;
	delete m_undoAct;
	delete m_aboutBabarStaticEditor;
	delete m_curs_box;
	delete m_curs_line;
	delete m_curs_green;
	delete m_curs_red;
	delete m_curs_erase;
	delete m_fileMenu;
	delete m_editMenu;
	delete m_helpMenu;
	delete m_fileToolBar;
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
	
	m_aboutBabarStaticEditor = new QAction(tr("About"), this);
	m_aboutBabarStaticEditor->setStatusTip(tr("About Babar Static Editor"));
	connect(m_aboutBabarStaticEditor, SIGNAL(triggered()), this, SLOT(aboutBabarStaticEditor()));
	
	m_saveAct = new QAction(QIcon("images/save.png"),tr("Save"), this);
	m_saveAct->setShortcuts(QKeySequence::Save);
	m_saveAct->setStatusTip(tr("Save the .col file"));
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));
		
	m_undoAct = new QAction(QIcon("images/undo.png"),tr("Undo"), this);
	m_undoAct->setShortcuts(QKeySequence::Undo);
	m_undoAct->setStatusTip(tr("Undo"));
	connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));
	
	m_curs_box = new QAction(QIcon("images/box.png"), tr("Box curs"), this);
	m_curs_box->setStatusTip("Simple cursor");
	connect(m_curs_box, SIGNAL(triggered()), this, SLOT(setCursBox()));
	
	m_curs_line = new QAction(QIcon("images/line.png"), tr("Line curs"), this);
	m_curs_line->setStatusTip("Trace lines");
	connect(m_curs_line, SIGNAL(triggered()), this, SLOT(setCursLine()));
	
	m_curs_green = new QAction(QIcon("images/green_curs.png"), tr("Down coll curs"), this);
	m_curs_green->setStatusTip("To print down collisions (green)");
	connect(m_curs_green, SIGNAL(triggered()), this, SLOT(setCursGreen()));
	
	m_curs_red = new QAction(QIcon("images/red_curs.png"), tr("Full coll curs"), this);
	m_curs_red->setStatusTip("To print full collisions (red)");
	connect(m_curs_red, SIGNAL(triggered()), this, SLOT(setCursRed()));
	
	m_curs_erase = new QAction(QIcon("images/erase_curs.png"), tr("No coll curs"), this);
	m_curs_erase->setStatusTip("To print no_collisions (no color)");
	connect(m_curs_erase, SIGNAL(triggered()), this, SLOT(setCursErase()));
	
	
}

void MainWindow::createMenus()
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
	m_fileMenu->addAction(m_saveAct);
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
	m_fileToolBar->addAction(m_saveAct);
	m_fileToolBar->addAction(m_undoAct);
	m_fileToolBar->addSeparator();
	m_fileToolBar->addAction(m_curs_box);
	m_fileToolBar->addAction(m_curs_line);
	m_fileToolBar->addSeparator();
	m_fileToolBar->addAction(m_curs_green);
	m_fileToolBar->addAction(m_curs_red);
	m_fileToolBar->addAction(m_curs_erase);

//~ 	editToolBar = addToolBar(tr("Edit"));
//~ 	editToolBar->addAction(cutAct);
//~ 	editToolBar->addAction(copyAct);
//~ 	editToolBar->addAction(pasteAct);	
}

void MainWindow::newFile()
{
	if (m_opened_file) {
		warningSave();
	}
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier .png",
			STATIC_DIR,  tr("Images (*.png *.xpm *.jpg)"));
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
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier .png",
			STATIC_DIR,  tr("Images (*.png *.xpm *.jpg)"));
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

void MainWindow::undo()
{
	std::cout << "undo" << std::endl;
	m_graphic_view->undo();
}

void MainWindow::aboutBabarStaticEditor()
{
	QMessageBox::information(this, "About us", "Babar Static Editor is a Qt tool for editing SuperBabar static objects. Read the manual for more informations. You can also visit our website: <a href=\"http://nalwarful.free.fr/Babar/jeu.php\"> SuperBabar </a>");

}

void MainWindow::setCursBox()
{
	m_graphic_view->setCursorShape(CURS_BOX);
}

void MainWindow::setCursLine()
{
	m_graphic_view->setCursorShape(CURS_LINE);
}

void MainWindow::setCursGreen()
{
	m_graphic_view->setCursorCol(DOWN_COLL);
}

void MainWindow::setCursRed()
{
	m_graphic_view->setCursorCol(FULL_COLL);	
}

void MainWindow::setCursErase()
{
	m_graphic_view->setCursorCol(NO_COLL);
}

void MainWindow::warningSave()
{
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
