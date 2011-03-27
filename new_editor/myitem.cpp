#include "myitem.h"
#include "data.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

MyItem::MyItem(QGraphicsPixmapItem *item, QString fileName):
	m_item(item),
	m_file_name(fileName)
{
	
}

MyItem::~MyItem()
{
	// TODO liberer??
}

QGraphicsPixmapItem *MyItem::getItem()
{
	return m_item;
}

void MyItem::edit()
{
	
}

void MyItem::moveItem(int x, int y)
{
	QGraphicsPixmapItem *item = this->getItem();
	item->setPos(item->x() + x, item->y() + y);
}

void MyItem::setPos(int x, int y)
{
	QGraphicsPixmapItem *item = this->getItem();
	item->setPos(x, y);	
}

MyItem *MyItem::selectItem(int x, int y)
{
	QGraphicsPixmapItem *item = this->getItem();
	if (item->x() <= x && x <= item->x() + item->boundingRect().width()
		&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {	
		return this;	
	}
	return NULL;
}

void MyItem::removeFromScene(QGraphicsScene *scene)
{
	scene->removeItem(getItem());
}

