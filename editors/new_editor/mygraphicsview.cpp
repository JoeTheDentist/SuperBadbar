
#include "mygraphicsview.h"
#include "myitem.h"
#include "data.h"
#include "babaritem.h"
#include "staticitem.h"
#include "monsteritem.h"
#include "eventitem.h"
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


MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
	QGraphicsView(scene, parent),
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
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_background = this->scene()->addRect(0, 0, m_xsize, m_ysize, QPen(), QBrush(QColor(255, 100, 100)));
	m_opened = true;
	QPixmap babarpix;
	babarpix.load(QString(BABAR_PIC_DIR) + "1/babar_0_0_0.png");
	QGraphicsPixmapItem *item = this->scene()->addPixmap(babarpix);
	m_babar_item = new BabarItem(item);
	m_data->addItem(m_babar_item);
}

void MyGraphicsView::loadFile(QString fileName)
{
	Analyser analyser;
	QPixmap image;
	int x, y, zbuffer, age;
	QGraphicsPixmapItem *item = NULL;
	m_opened = true;
	analyser.open(fileName.toStdString());
	analyser.find_string("#Background#");
	newFile(QString::fromStdString(analyser.read_string()));
	analyser.find_string("#Babar#");
	x = analyser.read_int();
	y = analyser.read_int();
	age = analyser.read_int();
	m_babar_item->getItem()->setPos(x, y);
	m_babar_item->setBabarAge(age);
	analyser.find_string("#Statics#");
	int nbStatics = analyser.read_int();
	QString nameStatic;
	for (int i = 0; i < nbStatics; i ++) {
		nameStatic = QString::fromStdString(analyser.read_string());
		image.load(StaticItem::picPathFromEditor(nameStatic));
		item = this->scene()->addPixmap(image);
		std::cout << nameStatic.toStdString() << std::endl;
		x = analyser.read_int();
		y = analyser.read_int();
		zbuffer = analyser.read_int();
		item->setPos(x, y);
		m_data->addItem(new StaticItem(item, nameStatic, zbuffer));
	}
	analyser.find_string("#Monsters#");
	int nbMonsters = analyser.read_int();
	QString nameMonster;	
	QString classMonster;
	for (int i = 0; i < nbMonsters; i ++) {
		classMonster = QString::fromStdString(analyser.read_string());
		nameMonster = QString::fromStdString(analyser.read_string());
		image.load(MonsterItem::picPathFromEditor(nameMonster));
		item = this->scene()->addPixmap(image);
		x = analyser.read_int();
		y = analyser.read_int();
		item->setPos(x, y);
		m_data->addItem(new MonsterItem(item, nameMonster));
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
		image.load(EventItem::picPathFromEditor(nameEvent));
		item = this->scene()->addPixmap(image);
		x = analyser.read_int();
		y = analyser.read_int();
		item->setPos(x, y);
		m_data->addItem(new EventItem(item, nameEvent));
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
	} else if (event->button() == Qt::LeftButton) {
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
	(void)event; // ne sert à rien..
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
			QGraphicsPixmapItem *item = m_moved_item->getItem();
			item->setPos(item->x() + posClicX(event) - m_xprec, item->y() + posClicY(event) - m_yprec);
		} else if (m_curr_item) {
			m_curr_item->getItem()->setPos(posClicX(event), posClicY(event));
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
	m_data->saveData(str);
}

void MyGraphicsView::addBabar()
{
	m_curr_item = m_data->selectBabar();
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
	QPixmap image;
	fileName.chop(3); // Le fichier peut se terminer par col ou png mais on veut l'image
	fileName.append("png");
	image.load(fileName);
	QGraphicsPixmapItem *item = this->scene()->addPixmap(image);
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("statics/") + 8));
	fileName.chop(4);
	m_curr_item = new StaticItem(item, fileName);
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
	QPixmap image;

	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("monsters/") + 9));
	fileName.chop(5);	
	image.load(MonsterItem::picPathFromEditor(fileName));
	QGraphicsPixmapItem *item = this->scene()->addPixmap(image);	m_curr_item = new MonsterItem(item, fileName);	
}

void MyGraphicsView::addEvent()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Ouverture d'un fichier de monstre", EVENTS_DIR);
	if (fileName.isEmpty()) {
		return;
	}
	if (!(fileName.endsWith(EVENTS_EXT))) {
	 QMessageBox::critical(this, "File opening", "filename must ends with \".evt\"");
		return;
	}
	QPixmap image;

	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("events/") + 7));
	fileName.chop(4);	
	image.load(EventItem::picPathFromEditor(fileName));
	QGraphicsPixmapItem *item = this->scene()->addPixmap(image);	
	m_curr_item = new EventItem(item, fileName);	
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
		this->scene()->removeItem(item->getItem());
		m_data->removeItem(item);
	}	
}

void MyGraphicsView::copyItem(MyItem *item) 
{
	if (item) {
		if (m_copied_item) {
			// remove m_copied_item de la scene
			delete m_copied_item;
		}
		m_copied_item = item->duplicate();
	}
}

void MyGraphicsView::pastItem()
{
	if (m_copied_item && (m_copied_item != m_babar_item)) {
		MyItem *item = m_copied_item->duplicate();
		item->getItem()->setVisible(true);
		item->getItem()->setPos(this->horizontalScrollBar()->value() / m_zoom, this->verticalScrollBar()->value() / m_zoom);
		m_data->addItem(item);
	}
}
