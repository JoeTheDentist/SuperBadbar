#include "myitem.h"
#include "data.h"
#include <QGraphicsItem>


MyItem::MyItem(QGraphicsItem *item, QString fileName):
	m_item(item),
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

void MyItem::saveItem(QTextStream &out)
{
	out << "plop" << endl;
}

