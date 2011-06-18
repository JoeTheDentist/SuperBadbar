
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


MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
	QGraphicsView(scene, parent),
	m_histo()
{
	m_opened = false;
	m_background = NULL;
	m_mouse_pressed = false;
	m_curs_shape = CURS_BOX;
}

MyGraphicsView::~MyGraphicsView()
{
	delete m_collisions_matrix;
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
		m_collisions_matrix = new QCollisionsMatrix(m_coll_width, m_coll_height);
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
		for (int i = 0; i < m_coll_height; i++) {
			for (int j = 0; j < m_coll_width; j++) {
				flux >> coll;
				setBox(coll, j * BOX_SIZE, i * BOX_SIZE, false);
				std::cout << coll << std::endl;
			}
		}	
	}
	m_coll_curs = DOWN_COLL;
	m_opened = true;
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
	m_mouse_pressed = true;
	if (m_opened) {
		switch(m_curs_shape) {
		case CURS_BOX:
			m_histo.newSequence();
			m_xprec = posClicX(event);
			m_yprec = posClicY(event);		
			draw_line(m_coll_curs, posClicX(event), posClicY(event), posClicX(event), posClicY(event));
			break;
		case CURS_LINE:
			m_histo.newSequence();
			m_xprec = posClicX(event);
			m_yprec = posClicY(event);
			draw_line(m_coll_curs, posClicX(event), posClicY(event), posClicX(event), posClicY(event));			
			break;
		default:
			break;
		}                                                     
	}
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	m_mouse_pressed = false;
	if (m_opened) {
		switch(m_curs_shape) {
		case CURS_BOX:
			break;
		case CURS_LINE:
			draw_line(m_coll_curs, m_xprec, m_yprec, posClicX(event), posClicY(event));
			break;
		default:
			break;
		}
	}
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) 
{
	if (m_opened && m_mouse_pressed) {
		switch(m_curs_shape) {
		case CURS_BOX:
			draw_line(m_coll_curs, m_xprec, m_yprec, posClicX(event), posClicY(event));
			m_xprec = posClicX(event);
			m_yprec = posClicY(event);
			break;
		case CURS_LINE:
			undo();
			m_histo.newSequence();
			draw_line(m_coll_curs, m_xprec, m_yprec, posClicX(event), posClicY(event));			
			break;
		default:
			break;
		}
	}	
}

void MyGraphicsView::setBox(int coll, int x, int y, bool save)
{
	int i = x / BOX_SIZE;
	int j = y / BOX_SIZE;
	if (save)
		m_histo.saveColl(m_collisions_matrix->coll(i, j),i, j);
	m_collisions_matrix->setColl(coll, i, j);
	QGraphicsItem *item;
	item = m_collisions_matrix->item(i, j);
	if (item) {
		this->scene()->removeItem(item);
		delete item;
	}
	if (coll) {
		if (coll == DOWN_COLL)
			item = this->scene()->addPixmap(m_down_pic);
		else if (coll == FULL_COLL)
			item = this->scene()->addPixmap(m_full_pic); 
		item->setZValue(5);
		item->setPos(i * BOX_SIZE, j * BOX_SIZE);
		m_collisions_matrix->setItem(item, i, j);
	} else {
		m_collisions_matrix->setColl(NO_COLL, i, j);
		m_collisions_matrix->setItem(NULL, i, j);
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
	m_collisions_matrix->save(str);
}

void MyGraphicsView::draw_line(int coll, float x, float y, float X, float Y)
{
	float i = x , j = y, a = (Y-y)/(X-x);
	setBox(coll, x, y);
	if (a < 0)
		a = -a;
	if (a < 1) {
		if (x < X){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (Y-j)/(X-i);
		for (; i < X; i += BOX_SIZE) {
			j+= a * BOX_SIZE;
			setBox(coll, i, j);
		}
	}
	else {
		if (y < Y){
			i = x; j = y;
		}
		else {
			i = X; j = Y; X = x; Y = y;
		}
		a = (X-i)/(Y-j);
		for (; j < Y; j += BOX_SIZE) {
			i+= a * BOX_SIZE;
			setBox(coll, i, j);
		}	
	}
}

void MyGraphicsView::setCursorShape(int shape)
{
	m_curs_shape = shape;
}

void MyGraphicsView::setCursorCol(int col) 
{
	m_coll_curs = col;
}

void MyGraphicsView::undo()
{
	if (m_histo.canUndo()) {
		std::list<collAndPos>::iterator it;
		for (it = m_histo.lastSequence()->begin(); it != m_histo.lastSequence()->end(); it++) {
			setBox((*it).coll, (*it).i*BOX_SIZE, (*it).j*BOX_SIZE, false);
		}
		m_histo.popLastSequence();
	}
}
