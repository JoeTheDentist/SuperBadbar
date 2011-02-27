#include "myitem.h"
#include "data.h"
#include <QGraphicsItem>
#include <QGraphicsView>


MyItem::MyItem(QGraphicsItem *item, QString fileName):
	m_item(item),
	m_file_name(fileName)
{
	
}

MyItem::MyItem(const MyItem &item) 
{
//~ 	m_item = item.m_item->scene()->addI
}

MyItem::~MyItem()
{
	// TODO liberer??
}

QGraphicsItem *MyItem::getItem()
{
	return m_item;
}

void MyItem::saveItem(QTextStream &out)
{
	out << "plop" << endl;
}

