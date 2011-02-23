
#include "mygraphicsview.h"
#include "myitem.h"
#include "data.h"
#include "staticitem.h"
#include "analyser.h"

#include <iostream>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>


MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
	QGraphicsView(scene, parent),
	m_data(new Data()),
	m_opened(false),
	m_mouse_pressed(false),
	m_ctrl_pressed(false),
	m_curr_item(NULL),
	m_selected_item(NULL),
	m_del_curs(NULL),
	m_zoom(1)
{
	setMouseTracking(true); // pour que mouseMoveEvent soit declenche sans que la souris soit pressee
}

MyGraphicsView::~MyGraphicsView()
{
	delete m_data;
}

void MyGraphicsView::newFile(QString backgroundName)
{
	// TODO
	QPixmap image;
	QGraphicsItem *item = NULL;
	image.load(backgroundName, 0, Qt::AutoColor);
	item = this->scene()->addPixmap(image);
	m_data->setBackground(item, backgroundName);
	m_xsize = image.width();
	m_ysize = image.height();
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_opened = true;
}

void MyGraphicsView::loadFile(QString fileName)
{
	Analyser analyser;
	QPixmap image;
	QGraphicsItem *item = NULL;
	m_opened = true;
	analyser.open(fileName.toStdString());
	analyser.find_string("#Background#");
	newFile(QString::fromStdString(analyser.read_string()));
	analyser.find_string("#Statics#");
	int nbStatics = analyser.read_int();
	QString nameStatic;
	for (int i = 0; i < nbStatics; i ++) {
		nameStatic = QString::fromStdString(analyser.read_string());
		image.load(StaticItem::editorRelativePath(nameStatic));
		item = this->scene()->addPixmap(image);
		item->setPos(analyser.read_int(), analyser.read_int());
		m_data->addItem(new StaticItem(item, nameStatic));
		analyser.read_int(); // TODO: champ a revoir
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
	m_mouse_pressed = true;
	if (m_opened && !m_del_curs) {
		if (m_curr_item) {
			if (event->button() == Qt::LeftButton) {
				m_data->addItem(m_curr_item);
				m_curr_item = NULL;
			} else if (event->button() == Qt::RightButton) {
				this->scene()->removeItem(m_curr_item->getItem());
				delete m_curr_item->getItem();
				delete m_curr_item;
				m_curr_item = NULL;				
			}
		} else if (m_data->selectItem(posClicX(event), posClicY(event))) {
			m_selected_item = m_data->selectItem(posClicX(event), posClicY(event));
		}			
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
			if (item) {
				m_data->removeItem(item);
				this->scene()->removeItem(item->getItem());
//~ 				delete item;
				this->scene()->removeItem(m_del_curs);
				delete m_del_curs;
				m_del_curs = NULL;
			}
		}
		if (m_selected_item) {
			m_selected_item = NULL;
		}
	}
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) 
{
	if (m_opened) {
		if (m_del_curs) {
			m_del_curs->setPos(posClicX(event), posClicY(event));
		} else if (m_selected_item) {
			QGraphicsItem *item = m_selected_item->getItem();
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
	if (event->key() == Qt::Key_Control) {
		m_ctrl_pressed = true;
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
	QGraphicsItem *item = this->scene()->addPixmap(image);
	fileName = fileName.right(fileName.size() - (fileName.lastIndexOf("statics/") + 8));
	fileName.chop(4);
	m_curr_item = new StaticItem(item, fileName);
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
