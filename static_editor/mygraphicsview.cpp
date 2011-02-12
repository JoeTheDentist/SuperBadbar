
#include "mygraphicsview.h"
#include <iostream>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsItem>
#include <QMouseEvent>



MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent): QGraphicsView(scene, parent)
{
	m_opened = false;
	m_background = NULL;
}

void MyGraphicsView::loadFile(QString fileName)
{
	QPixmap image;
	image.load(fileName, 0, Qt::AutoColor);
	m_down_pic.load("images/down_coll.png");
	m_full_pic.load("images/full_coll.png");
	if (m_background) 
		this->scene()->removeItem(m_background);
	m_background = this->scene()->addPixmap(image);
	m_xsize = image.width();
	m_ysize = image.height();
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_coll_width = m_xsize / BOX_SIZE + 1;
	m_coll_height = m_ysize / BOX_SIZE + 1;
	loadCol(fileName);
	m_coll_curs = 1;
	m_opened = true;
}

void MyGraphicsView::loadCol(QString fileName)
{
	if (fileName.isEmpty()) {
		std::cout << "yop " << m_coll_width << " " << m_coll_height << std::endl;
		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
	} else {
		m_collisions_matrix = new QCollisionsMatrix(fileName);
	}
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
	std::cout << event->x() + this->horizontalScrollBar()->value() 
		<< " " << event->y() + this->verticalScrollBar()->value()  << std::endl;
	if (m_opened) {
		m_collisions_matrix->setColl(m_coll_curs, posClicX(event) % BOX_SIZE, posClicY(event) % BOX_SIZE);
		QGraphicsItem *item = this->scene()->addPixmap(m_down_pic);
		item->setPos((posClicX(event)*BOX_SIZE)/BOX_SIZE, (posClicY(event)*BOX_SIZE)/BOX_SIZE);
		m_collisions_matrix->setItem(item, posClicX(event) % BOX_SIZE, posClicY(event) % BOX_SIZE);
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

void MyGraphicsView::refreshScene()
{
	for (int i = 0; i < m_coll_width; i++) {
		for (int j = 0; j < m_coll_height; j++) {
			if (m_collisions_matrix->item(i,j)) {
				
			}
		}
	}
}
