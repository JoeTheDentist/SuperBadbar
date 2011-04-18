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
//~ #include "qnewfilewindow.h"


MainWindow::MainWindow():
	m_graphic_scene(new QGraphicsScene()),
	m_graphic_view(new MyGraphicsView(m_graphic_scene, this)),	
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
	m_addSet(NULL),
	m_addStatic(NULL),
	m_addPlatform(NULL),
	m_addMonster(NULL),
	m_addEvent(NULL),
	m_addTrigger(NULL),
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
	delete m_fileMenu;
	delete m_editMenu;
	delete m_helpMenu;
	delete m_addSet;
	delete m_addStatic;
	delete m_addPlatform;
	delete m_addMonster;
	delete m_addEvent;
	delete m_addTrigger;
	delete m_addBabar;
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
	
	m_saveAsAct = new QAction(QIcon("images/saveas.png"),tr("Save as"), this); 
	m_saveAsAct->setStatusTip(tr("Save as"));
	connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));	
		
	m_addBabar = new QAction(QIcon("images/addbabar.png"),tr("addBabar"), this); 
	m_addBabar->setStatusTip(tr("Change the Babar's start position"));
	connect(m_addBabar, SIGNAL(triggered()), this, SLOT(addBabar()));	
		
	m_addSet = new QAction(QIcon("images/addset.png"),tr("AddSet"), this); 
	m_addSet->setStatusTip(tr("Add a set to the level"));
	connect(m_addSet, SIGNAL(triggered()), this, SLOT(addSet()));	

	m_addStatic = new QAction(QIcon("images/addstatic.png"),tr("AddStatic"), this); 
	m_addStatic->setStatusTip(tr("Add a static to the level"));
	connect(m_addStatic, SIGNAL(triggered()), this, SLOT(addStatic()));	
	
	m_addPlatform = new QAction(QIcon("images/addplatform.png"),tr("AddPlatform"), this); 
	m_addPlatform->setStatusTip(tr("Add a platform to the level"));
	connect(m_addPlatform, SIGNAL(triggered()), this, SLOT(addPlatform()));	

	m_addMonster = new QAction(QIcon("images/addmonster.png"),tr("AddMonster"), this); 
	m_addMonster->setStatusTip(tr("Add a monster to the level"));
	connect(m_addMonster, SIGNAL(triggered()), this, SLOT(addMonster()));	
	
	m_addEvent = new QAction(QIcon("images/addevent.png"),tr("AddEvent"), this); 
	m_addEvent->setStatusTip(tr("Add an event to the level"));
	connect(m_addEvent, SIGNAL(triggered()), this, SLOT(addEvent()));	
	
	m_addTrigger = new QAction(QIcon("images/addtrigger.png"),tr("AddTrigger"), this); 
	m_addTrigger->setStatusTip(tr("Add a trigger to the level"));
	connect(m_addTrigger, SIGNAL(triggered()), this, SLOT(addTrigger()));	
	
	m_deleteItem = new QAction(QIcon("images/deleteitem.png"),tr("Delete item"), this); // TODO changer image
	m_deleteItem->setStatusTip(tr("Delete an item from the level"));
	connect(m_deleteItem, SIGNAL(triggered()), this, SLOT(deleteItem()));	
}

 void MainWindow::createMenus()
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
	m_fileMenu->addAction(m_saveAct);
	m_fileMenu->addAction(m_saveAsAct);
	m_fileMenu->addAction(m_exitAct);
	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	m_editMenu->addAction(m_addBabar);
	m_editMenu->addAction(m_addSet);
	m_editMenu->addAction(m_addStatic);
	m_editMenu->addAction(m_addPlatform);
	m_editMenu->addAction(m_addMonster);
	m_editMenu->addAction(m_addEvent);
	m_editMenu->addAction(m_addTrigger);
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
	m_fileToolBar->addAction(m_addBabar);
	m_fileToolBar->addAction(m_addSet);
	m_fileToolBar->addAction(m_addStatic);
	m_fileToolBar->addAction(m_addPlatform);
	m_fileToolBar->addAction(m_addMonster);
	m_fileToolBar->addAction(m_addEvent);
	m_fileToolBar->addAction(m_addTrigger);
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

void MainWindow::addBabar()
{
	m_graphic_view->addBabar();
}

void MainWindow::addSet()
{
	if (m_opened_file)
		m_graphic_view->addSet();
}

void MainWindow::addStatic()
{
	if (m_opened_file)
		m_graphic_view->addStatic();
}

void MainWindow::addPlatform()
{
	if (m_opened_file)
		m_graphic_view->addPlatform();
}

void MainWindow::addMonster()
{
	if (m_opened_file)
		m_graphic_view->addMonster();
}

void MainWindow::addEvent()
{
	if (m_opened_file)
		m_graphic_view->addEvent();
}

void MainWindow::addTrigger()
{
	if (m_opened_file)
		m_graphic_view->addTrigger();
}

void MainWindow::deleteItem()
{
	m_graphic_view->activeDeleteItem();
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
