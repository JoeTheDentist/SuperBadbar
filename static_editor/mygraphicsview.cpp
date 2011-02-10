
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
	/* Temporaire */
	QGraphicsItem *item;
	QPixmap image;
	image.load("plop.png", 0, Qt::AutoColor);
	item = this->scene()->addPixmap(image);
	/* ---------- */	
}


void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
	std::cout << event->x() + this->horizontalScrollBar()->value() 
		<< " " << event->y() + this->verticalScrollBar()->value()  << std::endl;
}
