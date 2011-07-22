
#include "mygraphicsview.h"
#include "myitem.h"
#include "data.h"
#include "babaritem.h"
#include "setitem.h"
#include "staticitem.h"
#include "movingplatformitem.h"
#include "fallingplatformitem.h"
#include "monsteritem.h"
#include "eventitem.h"
#include "triggeritem.h"
#include "utils.h"

#include <iostream>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsColorizeEffect>
#include <QProcess>
#include <QGraphicsSimpleTextItem>
#include <QStatusBar>
#include "mainwindow.h"


#ifndef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent, MainWindow *mainWindow):
	QGraphicsView(scene, parent),
	m_state(e_fileClosed),
	m_main_window(mainWindow),
	m_file_name(),
	m_data(new Data()),
	m_mouse_pressed(false),
	m_ctrl_pressed(false),
	m_babar_item(NULL),
	m_curr_item(NULL),
	m_selected_item(NULL),
	m_copied_item(NULL),
	m_del_curs(NULL),
	m_zoom(1),
	m_background(NULL),
	m_statusBar(NULL)

{
	MyItem::setView(this);
	setMouseTracking(true); // pour que mouseMoveEvent soit declenche sans que la souris soit pressee
}

MyGraphicsView::~MyGraphicsView()
{
	delete m_data;
}

void MyGraphicsView::newFile(QString backgroundName)
{
	m_data->initData(backgroundName);
	m_xsize = m_data->levelWidth();
	m_ysize = m_data->levelHeight();
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_background = this->scene()->addRect(0, 0, m_xsize, m_ysize, QPen(), QBrush(QColor(255, 100, 100)));
	m_babar_item = new BabarItem(this->scene());
	addToData(m_babar_item);
	m_ctrl_pressed = false;
	setStateNone();
}

void MyGraphicsView::loadFile(QString fileName)
{
	m_file_name = fileName;
	Analyser analyser;
	int x, y, zbuffer, age;
	unsigned int colVal;
	MyItem *myitem = NULL;
	analyser.open(fileName.toStdString());
	analyser.find_string("#Background#");
	newFile(QString::fromStdString(BACKGROUND_DIR + analyser.read_string()));
	analyser.find_string("#Babar#");
	x = analyser.read_int();
	y = analyser.read_int();
	age = analyser.read_int();
	m_babar_item->setPos(x, y);
	m_babar_item->setBabarAge(age);
	if (analyser.find_string("#Music#")) {
		m_data->setMusicName(QString::fromStdString(analyser.read_string()));
	}
	if (analyser.find_string("#Sets#")) {
		int nbSets = analyser.read_int();
		QString nameSet;
		for (int i = 0; i < nbSets; i ++) {
			nameSet = QString::fromStdString(analyser.read_string());
			x = analyser.read_int();
			y = analyser.read_int();
			myitem = new SetItem(this->scene(), nameSet);
			myitem->setPos(x, y);
			addToData(myitem);
		}
	}
	
	analyser.find_string("#Statics#");
	int nbStatics = analyser.read_int();
	QString nameStatic;
	for (int i = 0; i < nbStatics; i ++) {
		nameStatic = QString::fromStdString(analyser.read_string());
		std::cout << nameStatic.toStdString() << std::endl;
		x = analyser.read_int();
		y = analyser.read_int();
		colVal = analyser.read_unsigned_int();
		zbuffer = analyser.read_int();
		myitem = new StaticItem(this->scene(), nameStatic, zbuffer);
		myitem->setPos(x, y);
		addToData(myitem);
	}
	if (analyser.find_string("#FallingPlatforms#")) {
		int nbFPlatforms = analyser.read_int();
		QString nameFPlatform;
		for (int i = 0; i < nbFPlatforms; i ++) {
			nameFPlatform = QString::fromStdString(analyser.read_string());
			std::cout << nameFPlatform.toStdString() << std::endl;
			x = analyser.read_int();
			y = analyser.read_int();
			myitem = new FallingPlatformItem(this->scene(), nameFPlatform);
			myitem->setPos(x, y);
			addToData(myitem);
		}
	}
	
	analyser.find_string("#MovingPlatforms#");
	int nbPlatforms = analyser.read_int();
	for (int i = 0; i < nbPlatforms; i++) {
		MovingPlatformItem *temp = new MovingPlatformItem(this->scene(), QString::fromStdString(analyser.read_string()), analyser);
		addToData(temp);
	}
	analyser.find_string("#Monsters#");
	int nbMonsters = analyser.read_int();
	QString nameMonster;
	for (int i = 0; i < nbMonsters; i ++) {
		analyser.read_string(); // on ignore la classe du monstre
		nameMonster = QString::fromStdString(analyser.read_string());
		x = analyser.read_int();
		y = analyser.read_int();
		myitem = new MonsterItem(this->scene(), nameMonster);
		myitem->setPos(x, y);
		addToData(myitem);
	}
	analyser.find_string("#Events#");
	int nbEvents = analyser.read_int();
	QString nameEvent;
	QString classEvent;
	for (int i = 0; i < nbEvents; i ++) {
		classEvent = QString::fromStdString(analyser.read_string());
		if (classEvent != "event") {
			std::cout << "Erreur dans le fichier chargé ou l'éditeur n'est plus à jour!" << std::endl;
		}
		nameEvent = QString::fromStdString(analyser.read_string());
		x = analyser.read_int();
		y = analyser.read_int();
		myitem = new EventItem(this->scene(), nameEvent);
		myitem->setPos(x, y);
		addToData(myitem);
	}
	
	analyser.find_string("#Triggers#");
	int nbTriggers = analyser.read_int();
	for (int i = 0; i < nbTriggers; i ++) {
		analyser.find_next_string("#trig#");
		myitem = new TriggerItem(this->scene(), m_file_name, &analyser);
		addToData(myitem);
	}
	m_ctrl_pressed = false;
	analyser.close();
}

int MyGraphicsView::posClicX(QMouseEvent *event)
{
	return (event->x() + this->horizontalScrollBar()->value()) / m_zoom ;
}

int MyGraphicsView::posClicY(QMouseEvent *event)
{
	return (event->y() + this->verticalScrollBar()->value()) / m_zoom ;
}

void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		deSelectItem();
		m_mouse_pressed = true;
		if (fileOpened() && (m_state != e_erasingItem)) {
			if (m_state == e_addingItem) {
				// finalisation de l'ajout d'un item
				MyItem *curr = m_curr_item;
				setStateNone();
				addToData(curr);
				curr->signalEndOfAdding();
			
			} else if (m_data->selectItem(posClicX(event), posClicY(event))) {
				// selection d'un item
				m_curr_item = m_data->selectItem(posClicX(event), posClicY(event));
				if (m_curr_item) {
					setStateMovingItem(m_curr_item);
				}
				selectItem(m_curr_item);
			}
		}
	} else if (event->button() == Qt::RightButton && fileOpened()) {
		if (!m_del_curs && (m_state == e_addingItem)) {
			// annulation d'un ajout
			this->scene()->removeItem(m_curr_item->getItem());
			delete m_curr_item->getItem();
			delete m_curr_item;
			setStateNone();
		} else if (m_data->selectItem(posClicX(event), posClicY(event))) {
			// clic droit sur un objet
			m_data->selectItem(posClicX(event), posClicY(event))->rightClic(event->x(), event->y());
		}                                                 
	}
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (fileOpened()) {
		MyItem *item = m_data->selectItem(posClicX(event), posClicY(event));
		if (item) {
			item->edit();
		} else {
			mousePressEvent(event);
		}
	}
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	m_mouse_pressed = false;
	if (fileOpened()) {
		if (m_state == e_erasingItem) {
			// suppression definitive d'un objet pointe par la souris
			MyItem *item = NULL;
			item = m_data->selectItem(posClicX(event), posClicY(event));
			deleteFromEditor(item);
			this->scene()->removeItem(m_del_curs);
			delete m_del_curs;
			setStateNone();
		}
		if (m_state == e_movingItem) {
			setStateNone();
		}
	}
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	if (fileOpened()) {
		if (m_state == e_erasingItem) {
			m_del_curs->setPos(posClicX(event), posClicY(event));
		} else if (m_state == e_movingItem || m_state == e_addingItem) {
			m_curr_item->moveItem(posClicX(event) - m_xprec, posClicY(event) - m_yprec, posClicX(event), posClicY(event));
		} 
		m_xprec = posClicX(event);
		m_yprec = posClicY(event);
		if (m_statusBar) {
			// affichage des coordonnees de la souris
			QString s1;
			QString s2;
			s1.setNum(m_xprec);
			s2.setNum(m_yprec);
			m_statusBar->showMessage((s1 + " " + s2));
		}
	}

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
	if (m_ctrl_pressed) {
		if (event->delta() > 0) {
			for (int i = 0; i < event->delta(); i ++)
				zoom(0.995);
		} else {
			for (int i = 0; i < -event->delta(); i ++)
				zoom(1/0.995);
		}
	} else {
		QGraphicsView::wheelEvent(event); // scroll normal dans la fenetre
	}
}

void horror_function(QString level_name)
{
	#ifndef WIN32
	QProcess::execute(QString("../src/superbabar ") + "-level " + substringAfter(level_name, "levels/"));
	#else
	QProcess::execute(QString("../src/babar.exe"));
	#endif
}

void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Control:
			m_ctrl_pressed = true;
			break;
		case Qt::Key_Delete:
			if (m_selected_item) {
				deleteFromEditor(m_selected_item);
				setStateNone();
				break;
		case Qt::Key_C:
			copyItem(m_selected_item);
			break;
		case Qt::Key_P:
			horror_function(m_file_name);
			break;
		case Qt::Key_V:
			pastItem();
			break;
			}
		default:
			break;
	}
}

void MyGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control) {
		m_ctrl_pressed = false;
	}
}

qreal MyGraphicsView::xsize()
{
	return m_xsize;
}

qreal MyGraphicsView::ysize()
{
	return m_ysize;
}

void MyGraphicsView::save(QString str)
{
	m_file_name = str;
	m_data->saveData(str);
}

void MyGraphicsView::setMusic()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choix de la musique", MUSIC_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	fileName = substringAfter(fileName, "music/");
	m_data->setMusicName(fileName);
	m_ctrl_pressed = false;	
}

void MyGraphicsView::createNewBabar()
{
	m_curr_item = m_data->selectBabar();
}

void MyGraphicsView::createNewSet()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de set", SET_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!fileName.endsWith(".png")) {
	 QMessageBox::critical(this, "File opening", "filename must ends with  \".png\"");
		return;
	}
	int cutRight = 0;
	for (cutRight = fileName.size() - 1; fileName[cutRight] != '_'; cutRight--) {
		if (cutRight == 0)
			std::cerr << "Erreur dans le format d'une animation: doit contenir '_'" << std::endl;		
	}
	fileName = fileName.left(cutRight);
	fileName = substringAfter(fileName, "animations/");

	setStateAddingItem(new SetItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::createNewStatic()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de static", STATIC_DIR,  tr("Images (*.png)"));
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".col") || fileName.endsWith(".png"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".col\" or \".png\"");
		return;
	}
	fileName = substringAfter(fileName, "statics/");
	fileName = suppressExtension(fileName);
	setStateAddingItem(new StaticItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::addMovingPlatform()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de platform", STATIC_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".col") || fileName.endsWith(".png"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".col\" or \".png\"");
		return;
	}
	QPixmap image;
	fileName = substringAfter(fileName, "statics/");
	fileName = suppressExtension(fileName);
	setStateAddingItem(new MovingPlatformItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::addFallingPlatform()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de falling platform", STATIC_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".col") || fileName.endsWith(".png"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".col\" or \".png\"");
		return;
	}
	fileName = substringAfter(fileName, "statics/");
	fileName = suppressExtension(fileName);
	setStateAddingItem(new FallingPlatformItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::createNewMonster()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de monstre", MONSTERS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".mstr"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".mstr\"");
		return;
	}
	fileName = substringAfter(fileName, "monsters/");
	fileName = suppressExtension(fileName);
	setStateAddingItem(new MonsterItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::createNewEvent()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier event", EVENTS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(EVENTS_EXT))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".evt\"");
		return;
	}

	fileName = substringAfter(fileName, "events/");
	fileName = suppressExtension(fileName);
	setStateAddingItem(new EventItem(this->scene(), fileName));
	m_ctrl_pressed = false;
}

void MyGraphicsView::createNewTrigger()
{
	setStateAddingItem(new TriggerItem(this->scene(), m_file_name));	
}

void MyGraphicsView::setStateAddingItem(MyItem *item)
{
	m_state = e_addingItem;
	m_curr_item = item;
	m_curr_item->setStateBeingAdded();
}

void MyGraphicsView::setStateMovingItem(MyItem *item)
{
	setStateNone();
	m_state = e_movingItem;
	m_curr_item = item;
}

void MyGraphicsView::setStateErasingItem()
{
	setStateNone();
	QPixmap image;
	image.load("images/deleteitem.png");
	m_del_curs = this->scene()->addPixmap(image);
	m_state = e_erasingItem;
}

void MyGraphicsView::setStateNone() 
{
	m_state = e_none;
	m_curr_item = NULL;
	m_del_curs = NULL;
	m_curr_item = NULL;
}

void MyGraphicsView::zoom(qreal z)
{
	m_zoom *= z;
	this->scale(z, z);
}

void MyGraphicsView::selectItem(MyItem *item)
{
	deSelectItem();
	m_selected_item = item;
	m_selected_item->setStateSelected();
	m_data->upInStack(item);
}

void MyGraphicsView::deSelectItem()
{
	if (m_selected_item) {
		m_selected_item->setStateNothing();
	}
	m_selected_item = NULL;
}

void MyGraphicsView::deleteFromEditor(MyItem *item)
{
	if (item && item != m_babar_item) {
		deSelectItem();
		item->removeFromScene(this->scene());
		m_data->removeItem(item);
	}
}

void MyGraphicsView::copyItem(MyItem *item)
{
	if (item) {
		if (m_copied_item) {
			// remove m_copied_item de la scene
			m_copied_item->removeFromScene(this->scene());
			delete m_copied_item;
		}
		m_copied_item = item->duplicate(this->scene());
	}
}

void MyGraphicsView::pastItem()
{
	if (m_copied_item && (m_copied_item != m_babar_item)) {
		MyItem *item = m_copied_item->duplicate(this->scene());
		item->setVisible(true);
		setStateAddingItem(item);
	}
}

void MyGraphicsView::addToData(MyItem *item)
{
	m_data->addItem(item);
}
