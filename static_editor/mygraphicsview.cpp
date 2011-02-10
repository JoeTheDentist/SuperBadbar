
#include "mygraphicsview.h"
#include <iostream>

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent): QGraphicsView(scene, parent)
{
	
}


void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
	std::cout << "yaaaaa" << std::endl;
}

void MyGraphicsView::resizeEvent ( QResizeEvent * event )
{
	std::cout << "plop" << std::endl;
}
