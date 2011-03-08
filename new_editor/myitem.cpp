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
