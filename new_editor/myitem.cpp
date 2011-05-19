#include "myitem.h"
#include "data.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsColorizeEffect>
#include "mygraphicsview.h"

MyGraphicsView *MyItem::m_view = NULL;


MyItem::MyItem(QGraphicsItem *item, QString fileName, miState state):
	m_item(item),
	m_state(state),
	m_file_name(fileName)
{
	
}

MyItem::~MyItem()
{
	// TODO liberer??
}

QGraphicsItem *MyItem::getItem()
{
	return m_item;
}

void MyItem::edit()
{
	
}

void MyItem::mouseMoved(int x, int y)
{
	if (isBeingAdded()) {
		moveItem(x, y);
	} else if (isBeingMoved()){
		moveItem(x, y);
	}
}

void MyItem::moveItem(int xrel, int yrel, int xabs, int yabs)
{
	QGraphicsItem *item = this->getItem();
	if (m_state == e_beingAdded) {
		setPos(xabs, yabs);
	} else {
		item->setPos(item->x() + xrel, item->y() + yrel);
	}
}

void MyItem::setPos(int x, int y)
{
	QGraphicsItem *item = this->getItem();
	item->setPos(x, y);	
}

MyItem *MyItem::selectItem(int x, int y)
{
	QGraphicsItem *item = this->getItem();
	if (item->x() <= x && x <= item->x() + item->boundingRect().width()
		&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {	
		setStateSelected();
		return this;	
	}
	return NULL;
}

void MyItem::signalEndOfAdding()
{
	m_view->setStateNone();
	setStateNothing();
}

void MyItem::setStateSelected()
{
	getItem()->setGraphicsEffect(new QGraphicsColorizeEffect());
	m_state = e_selected;
}

void MyItem::setStateNothing()
{
	if (isSelected()) {
		getItem()->setGraphicsEffect(NULL);
	}
	m_state = e_nothing;
}


void MyItem::removeFromScene(QGraphicsScene *scene)
{
	scene->removeItem(getItem());
}

void MyItem::setView(MyGraphicsView *view)
{
	m_view = view;
}

MyGraphicsView *MyItem::getView() 
{
	return m_view;
}

void MyItem::removeFromData(Data *data) 
{
	data->removeItem(this);
}
