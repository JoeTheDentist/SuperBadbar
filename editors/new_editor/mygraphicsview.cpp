
#include "mygraphicsview.h"
#include <iostream>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include "data.h"


MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
	m_data(NULL),
	QGraphicsView(scene, parent)
{
	m_opened = false;
	m_mouse_pressed = false;
}

MyGraphicsView::~MyGraphicsView()
{
	delete m_data;
}

void MyGraphicsView::loadFile(QString fileName, bool newFile)
{
	// TODO
	QPixmap image;
	QGraphicsItem *item = NULL;
	image.load(fileName, 0, Qt::AutoColor);
	item = this->scene()->addPixmap(image);
//~ 	m_down_pic.load("images/down_coll.png");
//~ 	m_full_pic.load("images/full_coll.png");
//~ 	if (m_background) 
//~ 		this->scene()->removeItem(m_background);
//~ 	m_background = this->scene()->addPixmap(image);
//~ 	m_background->setZValue(0);
//~ 	m_xsize = image.width();
//~ 	m_ysize = image.height();
//~ 	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
//~ 	this->resize(m_xsize, m_ysize);
//~ 	m_coll_width = m_xsize / BOX_SIZE + 1;
//~ 	m_coll_height = m_ysize / BOX_SIZE + 1;
//~ 	if (newFile) {
//~ 		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
//~ 	} else {
//~ 		fileName.chop(3);
//~ 		fileName.append("col");
//~ 		QFile file(fileName);
//~ 		file.open( QIODevice::ReadOnly | QIODevice::Text );
//~ 		QTextStream flux(&file);
//~ 		flux >> m_coll_width;
//~ 		flux >> m_coll_height;
//~ 		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
//~ 		int coll;
//~ 		for (int i = 0; i < m_coll_height; i++) {
//~ 			for (int j = 0; j < m_coll_width; j++) {
//~ 				flux >> coll;
//~ 				setBox(coll, j * BOX_SIZE, i * BOX_SIZE, false);
//~ 				std::cout << coll << std::endl;
//~ 			}
//~ 		}	
//~ 	}
//~ 	m_coll_curs = DOWN_COLL;
//~ 	m_opened = true;
}

int MyGraphicsView::posClicX(QMouseEvent *event)
{
	return event->x() + this->horizontalScrollBar()->value() ;
}

int MyGraphicsView::posClicY(QMouseEvent *event)
{
	return event->y() + this->verticalScrollBar()->value() ;
}

void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
	m_mouse_pressed = true;
	if (m_opened) {
		//TODO                                                 
	}
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	m_mouse_pressed = false;
	if (m_opened) {
		//TODO 
	}
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) 
{
	if (m_opened && m_mouse_pressed) {
		//TODO
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

	
