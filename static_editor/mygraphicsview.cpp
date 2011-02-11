
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


