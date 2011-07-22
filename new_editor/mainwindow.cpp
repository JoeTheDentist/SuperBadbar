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
#include <QStatusBar>
#include "utils.h"

//~ #include "qnewfilewindow.h"


MainWindow::MainWindow():
	m_graphic_scene(new QGraphicsScene()),
	m_graphic_view(new MyGraphicsView(m_graphic_scene, this, this)),	
	m_opened_file(false),
	m_file_name(),
	m_fileMenu(NULL),
	m_editMenu(NULL),
	m_helpMenu(NULL),
	m_newAct(NULL),
	m_openAct(NULL),
	m_exitAct(NULL),
	m_saveAct(NULL),
	m_aboutBabarEditor(NULL),
	m_setMusic(NULL),
	m_createNewBabar(NULL),
	m_createNewSet(NULL),
	m_createNewStatic(NULL),
	m_addMovingPlatform(NULL),
	m_addFallingPlatform(NULL),
	m_createNewMonster(NULL),
	m_createNewEvent(NULL),
	m_createNewTrigger(NULL),
	m_fileToolBar(NULL)
{
	setCentralWidget(m_graphic_view);
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
	delete m_setMusic;
	delete m_fileMenu;
	delete m_editMenu;
	delete m_helpMenu;
	delete m_createNewSet;
	delete m_createNewStatic;
	delete m_addMovingPlatform;
	delete m_addFallingPlatform;
	delete m_createNewMonster;
	delete m_createNewEvent;
	delete m_createNewTrigger;
	delete m_createNewBabar;
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

	m_setMusic = new QAction(QIcon("images/setmusic.png"), tr("Music"), this);
	m_setMusic->setStatusTip(tr("Chose a new music for this level"));
	connect(m_setMusic, SIGNAL(triggered()), this, SLOT(setMusic()));
	
	m_saveAct = new QAction(QIcon("images/save.png"),tr("Save"), this);
	m_saveAct->setShortcuts(QKeySequence::Save);
	m_saveAct->setStatusTip(tr("Save the .col file"));
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));	
	
	m_saveAsAct = new QAction(QIcon("images/saveas.png"),tr("Save as"), this); 
	m_saveAsAct->setStatusTip(tr("Save as"));
	connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));	

	m_createNewBabar = new QAction(QIcon("images/addbabar.png"),tr("createNewBabar"), this); 
	m_createNewBabar->setStatusTip(tr("Change the Babar's start position"));
	connect(m_createNewBabar, SIGNAL(triggered()), this, SLOT(createNewBabar()));	

	m_createNewSet = new QAction(QIcon("images/addset.png"),tr("createNewSet"), this); 
	m_createNewSet->setStatusTip(tr("Add a set to the level"));
	connect(m_createNewSet, SIGNAL(triggered()), this, SLOT(createNewSet()));	

	m_createNewStatic = new QAction(QIcon("images/addstatic.png"),tr("AddStatic"), this); 
	m_createNewStatic->setStatusTip(tr("Add a static to the level"));
	connect(m_createNewStatic, SIGNAL(triggered()), this, SLOT(createNewStatic()));	
	
	m_addMovingPlatform = new QAction(QIcon("images/addmovingplatform.png"),tr("AddMovingPlatform"), this); 
	m_addMovingPlatform->setStatusTip(tr("Add a moving moving platform to the level"));
	connect(m_addMovingPlatform, SIGNAL(triggered()), this, SLOT(addMovingPlatform()));	
 	
	m_addFallingPlatform = new QAction(QIcon("images/addfallingplatform.png"),tr("AddFallingPlatform"), this); 
	m_addFallingPlatform->setStatusTip(tr("Add a falling moving platform to the level"));
	connect(m_addFallingPlatform, SIGNAL(triggered()), this, SLOT(addFallingPlatform()));	
	
	m_createNewMonster = new QAction(QIcon("images/addmonster.png"),tr("AddMonster"), this); 
	m_createNewMonster->setStatusTip(tr("Add a monster to the level"));
	connect(m_createNewMonster, SIGNAL(triggered()), this, SLOT(createNewMonster()));	
	
	m_createNewEvent = new QAction(QIcon("images/addevent.png"),tr("AddEvent"), this); 
	m_createNewEvent->setStatusTip(tr("Add an event to the level"));
	connect(m_createNewEvent, SIGNAL(triggered()), this, SLOT(createNewEvent()));	
	
	m_createNewTrigger = new QAction(QIcon("images/addtrigger.png"),tr("AddTrigger"), this); 
	m_createNewTrigger->setStatusTip(tr("Add a trigger to the level"));
	connect(m_createNewTrigger, SIGNAL(triggered()), this, SLOT(createNewTrigger()));	
	
	m_deleteItem = new QAction(QIcon("images/deleteitem.png"),tr("Delete item"), this); // TODO changer image
	m_deleteItem->setStatusTip(tr("Delete an item from the level"));
	connect(m_deleteItem, SIGNAL(triggered()), this, SLOT(deleteItem()));	
}

 void MainWindow::createMenus()
{	
	statusBar()->showMessage(tr("Create or open a file"));
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
	m_fileMenu->addAction(m_saveAct);
	m_fileMenu->addAction(m_saveAsAct);
	m_fileMenu->addAction(m_exitAct);
	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	m_editMenu->addAction(m_setMusic);
	m_editMenu->addAction(m_createNewBabar);
	m_editMenu->addAction(m_createNewSet);
	m_editMenu->addAction(m_createNewStatic);
	m_editMenu->addAction(m_addMovingPlatform);
	m_editMenu->addAction(m_addFallingPlatform);
	m_editMenu->addAction(m_createNewMonster);
	m_editMenu->addAction(m_createNewEvent);
	m_editMenu->addAction(m_createNewTrigger);
	m_editMenu->addAction(m_deleteItem);
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
	m_fileToolBar->addAction(m_saveAsAct);
	m_fileToolBar->addAction(m_aboutBabarEditor);
	m_fileToolBar->addAction(m_setMusic);
	m_fileToolBar->addAction(m_createNewBabar);
	m_fileToolBar->addAction(m_createNewSet);
	m_fileToolBar->addAction(m_createNewStatic);
	m_fileToolBar->addAction(m_addMovingPlatform);
	m_fileToolBar->addAction(m_addFallingPlatform);
	m_fileToolBar->addAction(m_createNewMonster);
	m_fileToolBar->addAction(m_createNewEvent);
	m_fileToolBar->addAction(m_createNewTrigger);
	m_fileToolBar->addAction(m_deleteItem);
}

void MainWindow::newFile()
{
	QString backgroundName = QFileDialog::getOpenFileName(this, "Chose a background for your level", BACKGROUND_DIR);
	if (backgroundName.isEmpty()) {
		return;
	}
	if (!backgroundName.endsWith(".png")) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".png\"");
		return;
	}	
	m_file_name = "";                                                                 
	m_opened_file = true;
	m_graphic_view->newFile(backgroundName);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
}

void MainWindow::open()
{
	// TODO ici on triche
	QString fileName = QFileDialog::getOpenFileName(this, "Opening a level", LEVELS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!fileName.endsWith(".lvl")) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".lvl\"");
		return;
	}	
	m_file_name = fileName;
	m_opened_file = true;
	m_graphic_view->loadFile(m_file_name);
	setMaximumSize(	m_graphic_view->xsize() + m_graphic_view->verticalScrollBar()->width(), 
		m_graphic_view->ysize() + m_graphic_view->horizontalScrollBar()->height() +
		m_fileMenu->height() + m_fileToolBar->height());
	m_graphic_view->setStatusBar(statusBar());
}

void MainWindow::save()
{
	if (m_opened_file) {
		if (m_file_name == "")
			this->saveAs();
		else
			this->saveFile(m_file_name);
	}
}

void MainWindow::saveAs()
{
	if (m_opened_file) {
		QString fileName = QFileDialog::getSaveFileName(this, "Save as");
		m_file_name = fileName;
		this->saveFile(m_file_name);
	}
}

void MainWindow::saveFile(QString str)
{
	std::cout << "sauvegarde" << std::endl;
	m_graphic_view->save(str);
}

void MainWindow::aboutBabarEditor()
{
	QMessageBox::information(this, "About us", "Babar Editor is a graphic editor using Qt to design SuperBabar levels. \
		Read the manual for more informations. You can also visit our website: \
		<a href=\"http://nalwarful.free.fr/Babar/jeu.php\"> SuperBabar </a>");
}

void MainWindow::setMusic()
{
	m_graphic_view->setMusic();
}

void MainWindow::createNewBabar()
{
	m_graphic_view->createNewBabar();
}

void MainWindow::createNewSet()
{
	if (m_opened_file)
		m_graphic_view->createNewSet();
}

void MainWindow::createNewStatic()
{
	if (m_opened_file)
		m_graphic_view->createNewStatic();
}

void MainWindow::addMovingPlatform()
{
	if (m_opened_file)
		m_graphic_view->addMovingPlatform();
}

void MainWindow::addFallingPlatform()
{
	if (m_opened_file)
		m_graphic_view->addFallingPlatform();
}

void MainWindow::createNewMonster()
{
	if (m_opened_file)
		m_graphic_view->createNewMonster();
}

void MainWindow::createNewEvent()
{
	if (m_opened_file)
		m_graphic_view->createNewEvent();
}

void MainWindow::createNewTrigger()
{
	if (m_opened_file)
		m_graphic_view->createNewTrigger();
}

void MainWindow::deleteItem()
{
	m_graphic_view->setStateErasingItem();
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
