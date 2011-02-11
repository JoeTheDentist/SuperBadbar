
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
	m_background = NULL;
}

void MyGraphicsView::loadFile(QString fileName)
{
	QPixmap image;
	image.load(fileName, 0, Qt::AutoColor);
	if (m_background) 
		this->scene()->removeItem(m_background);
	m_background = this->scene()->addPixmap(image);
	m_xsize = image.width();
	m_ysize = image.height();
	m_coll_width = m_xsize / BOX_SIZE + 1;
	m_coll_height = m_ysize / BOX_SIZE + 1;
	loadCol("");
}

void MyGraphicsView::loadCol(QString fileName)
{
	if (fileName.isEmpty()) {
		m_collision_matrix = new int*[m_coll_width];
		for (int i = 0; i < m_coll_width; i++) {
			m_collision_matrix[i] = new int[m_coll_height];
			for (int j = 0; j < m_coll_height; j++)
				m_collision_matrix[i][j] = 0;
		}
	}
}

void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
	std::cout << event->x() + this->horizontalScrollBar()->value() 
		<< " " << event->y() + this->verticalScrollBar()->value()  << std::endl;
}

qreal MyGraphicsView::xsize()
{
	return m_xsize;
}

qreal MyGraphicsView::ysize()
{
	return m_ysize;
}


