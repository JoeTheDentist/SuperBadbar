
#include "mygraphicsview.h"
#include "myitem.h"
#include "data.h"
#include "babaritem.h"
#include "setitem.h"
#include "staticitem.h"
#include "monsteritem.h"
#include "eventitem.h"
#include "triggeritem.h"
#include "analyser.h"

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

#ifndef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
	QGraphicsView(scene, parent),
	m_file_name(),
	m_data(new Data()),
	m_opened(false),
	m_mouse_pressed(false),
	m_ctrl_pressed(false),
	m_babar_item(NULL),
	m_curr_item(NULL),
	m_selected_item(NULL),
	m_moved_item(NULL),
	m_copied_item(NULL),
	m_del_curs(NULL),
	m_zoom(1),
	m_background(NULL)
{
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
	std::cout << "OGH " << m_xsize << " " << m_ysize << std::endl;
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_background = this->scene()->addRect(0, 0, m_xsize, m_ysize, QPen(), QBrush(QColor(255, 100, 100)));
	m_opened = true;
	m_babar_item = new BabarItem(this->scene());
	m_data->addItem(m_babar_item);
}

void MyGraphicsView::loadFile(QString fileName)
{
	m_file_name = fileName;
	Analyser analyser;
	int x, y, zbuffer, age;
	MyItem *myitem = NULL;
	m_opened = true;
	analyser.open(fileName.toStdString());
	analyser.find_string("#Background#");
	newFile(QString::fromStdString(BACKGROUND_DIR + analyser.read_string()));
	analyser.find_string("#Babar#");
	x = analyser.read_int();
	y = analyser.read_int();
	age = analyser.read_int();
	m_babar_item->setPos(x, y);
	m_babar_item->setBabarAge(age);
	if (analyser.find_string("#Sets#")) {
		int nbSets = analyser.read_int();
		QString nameSet;
		for (int i = 0; i < nbSets; i ++) {
			nameSet = QString::fromStdString(analyser.read_string());
			std::cout << nameSet.toStdString() << std::endl;
			x = analyser.read_int();
			y = analyser.read_int();
			myitem = new SetItem(this->scene(), nameSet);
			myitem->setPos(x, y);
			m_data->addItem(myitem);
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
		zbuffer = analyser.read_int();
		myitem = new StaticItem(this->scene(), nameStatic, zbuffer);
		myitem->setPos(x, y);
		m_data->addItem(myitem);
	}
	analyser.find_string("#Platforms#");
	int nbPlatforms = analyser.read_int();
	QString platformNature;
	for (int i = 0; i < nbPlatforms; i++) {
		platformNature = QString::fromStdString(analyser.read_string());
		PlatformItem *temp = new PlatformItem(this->scene(), QString::fromStdString(analyser.read_string()), analyser);
		m_data->addItem(temp);
		temp->setNature(platformNature);
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
		m_data->addItem(myitem);
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
		m_data->addItem(myitem);
	}

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
		if (m_opened && !m_del_curs) {
			if (m_curr_item) {
				m_data->addItem(m_curr_item);
				m_curr_item = NULL;
			} else if (m_data->selectItem(posClicX(event), posClicY(event))) {
				m_moved_item = m_data->selectItem(posClicX(event), posClicY(event));
				selectItem(m_moved_item);
			}
		}
	} else if (event->button() == Qt::RightButton) {
		if (m_opened && !m_del_curs && m_curr_item) {
			this->scene()->removeItem(m_curr_item->getItem());
			delete m_curr_item->getItem();
			delete m_curr_item;
			m_curr_item = NULL;
		}
	}
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
	MyItem *item = m_data->selectItem(posClicX(event), posClicY(event));
	if (item) {
		item->edit();
	} else {
		mousePressEvent(event);
	}
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	m_mouse_pressed = false;
	if (m_opened) {
		if (m_del_curs) {
			MyItem *item = NULL;
			item = m_data->selectItem(posClicX(event), posClicY(event));
			deleteFromEditor(item);
			this->scene()->removeItem(m_del_curs);
			delete m_del_curs;
			m_del_curs = NULL;
		}
		if (m_moved_item) {
			m_moved_item = NULL;
		}
	}
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	if (m_opened) {
		if (m_del_curs) {
			m_del_curs->setPos(posClicX(event), posClicY(event));
		} else if (m_moved_item) {
			m_moved_item->moveItem(posClicX(event) - m_xprec, posClicY(event) - m_yprec);
		} else if (m_curr_item) {
			m_curr_item->setPos(posClicX(event), posClicY(event));
		}
	}
	m_xprec = posClicX(event);
	m_yprec = posClicY(event);
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
    	QProcess::execute(QString("../src/babar ") + "-level " + level_name);
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
				m_selected_item = NULL;
				m_moved_item = NULL;
				m_curr_item = NULL;
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

void MyGraphicsView::addBabar()
{
	m_curr_item = m_data->selectBabar();
}

void MyGraphicsView::addSet()
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
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("animations/") + 11));

	m_curr_item = new SetItem(this->scene(), fileName);
}

void MyGraphicsView::addStatic()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de static", STATIC_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".col") || fileName.endsWith(".png"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".col\" or \".png\"");
		return;
	}
//~ 	fileName.chop(3); // Le fichier peut se terminer par col ou png mais on veut l'image
//~ 	fileName.append("png");
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("statics/") + 8));
	fileName.chop(4);
	m_curr_item = new StaticItem(this->scene(), fileName);
}

void MyGraphicsView::addPlatform()
{
	// TODO: factoriser avec addStatic
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de platform", STATIC_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".col") || fileName.endsWith(".png"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".col\" or \".png\"");
		return;
	}
	QPixmap image;
//~ 	fileName.chop(3); // Le fichier peut se terminer par col ou png mais on veut l'image
//~ 	fileName.append("png");
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("statics/") + 8));
	fileName.chop(4);
	m_curr_item = new PlatformItem(this->scene(), fileName);
}

void MyGraphicsView::addMonster()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de monstre", MONSTERS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(".mstr"))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".mstr\"");
		return;
	}
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("monsters/") + 9));
	fileName.chop(5);
	m_curr_item = new MonsterItem(this->scene(), fileName);
}


void MyGraphicsView::addEvent()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier event", EVENTS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(EVENTS_EXT))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".evt\"");
		return;
	}

	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("events/") + 7));
	fileName.chop(4);
	m_curr_item = new EventItem(this->scene(), fileName);
}

void MyGraphicsView::addTrigger()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier event", EVENTS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(TRIGGERS_EXT))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".trg\"");
		return;
	}

	m_curr_item = new TriggerItem(this->scene(), fileName);	
}

void MyGraphicsView::activeDeleteItem()
{
	QPixmap image;
	image.load("images/deleteitem.png");
	m_del_curs = this->scene()->addPixmap(image);
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
	m_selected_item->getItem()->setGraphicsEffect(new QGraphicsColorizeEffect());
	m_data->upInStack(item);
}

void MyGraphicsView::deSelectItem()
{
	if (m_selected_item) {
		m_selected_item->getItem()->setGraphicsEffect(NULL);
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
		item->moveItem(this->horizontalScrollBar()->value() / m_zoom, this->verticalScrollBar()->value() / m_zoom);
		m_data->addItem(item);
	}
}
