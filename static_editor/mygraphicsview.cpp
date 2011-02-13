
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


MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent): QGraphicsView(scene, parent)
{
	m_opened = false;
	m_background = NULL;
	m_mouse_pressed = false;
}

void MyGraphicsView::loadFile(QString fileName, bool newFile)
{
	QPixmap image;
	image.load(fileName, 0, Qt::AutoColor);
	m_down_pic.load("images/down_coll.png");
	m_full_pic.load("images/full_coll.png");
	if (m_background) 
		this->scene()->removeItem(m_background);
	m_background = this->scene()->addPixmap(image);
	m_background->setZValue(0);
	m_xsize = image.width();
	m_ysize = image.height();
	this->scene()->setSceneRect(0, 0, m_xsize, m_ysize);
	this->resize(m_xsize, m_ysize);
	m_coll_width = m_xsize / BOX_SIZE + 1;
	m_coll_height = m_ysize / BOX_SIZE + 1;
	if (newFile) {
		loadCol("");
	} else {
		fileName.chop(3);
		fileName.append("col");
		QFile file(fileName);
		file.open( QIODevice::ReadOnly | QIODevice::Text );
		QTextStream flux(&file);
		flux >> m_coll_width;
		flux >> m_coll_height;
		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
		int coll;
		for (int i = 0; i < m_coll_width; i++) {
			for (int j = 0; j < m_coll_height; j++) {
				flux >> coll;
				setBox(coll, j * BOX_SIZE, i * BOX_SIZE);
				std::cout << coll << std::endl;
			}
		}	
	}
	m_coll_curs = DOWN_COLL;
	m_opened = true;
}

void MyGraphicsView::loadCol(QString fileName)
{
	if (fileName.isEmpty()) {
		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
	} else {
		m_collisions_matrix = new QCollisionsMatrix(fileName, this);
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
	std::cout << posClicX(event) << " " << posClicY(event) << std::endl;
	if (m_opened) {
		setBox(m_coll_curs, posClicX(event), posClicY(event));
		m_mouse_pressed = true;
	}
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	m_mouse_pressed = false;
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) 
{
	if (m_opened && m_mouse_pressed) {
		setBox(m_coll_curs, posClicX(event), posClicY(event));
	}	
}

void MyGraphicsView::setBox(int coll, int x, int y)
{
	m_collisions_matrix->setColl(coll, x / BOX_SIZE, y / BOX_SIZE);
	QGraphicsItem *item;
	if (coll) {
		item = this->scene()->addPixmap(m_down_pic);
		item->setZValue(5);
		item->setPos((x / (BOX_SIZE) * BOX_SIZE), (y / BOX_SIZE) * BOX_SIZE);
		m_collisions_matrix->setItem(item, x / BOX_SIZE, y / BOX_SIZE);
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

void MyGraphicsView::save(QString str)
{
	m_collisions_matrix->save(str);
}
