#include "staticitem.h"
#include <QGraphicsItem>
#include <iostream>
#include "paths.h"

StaticItem::StaticItem(QGraphicsItem *item, QString fileName):
	MyItem(item, fileName)
{
}

StaticItem::~StaticItem()
{
	
}

void StaticItem::saveItem(QTextStream &out)
{
	out << m_file_name << " " << m_item->x() << " " << m_item->y() << " " << 0 << endl;
}

void StaticItem::addToData(Data *data)
{
	data->addStaticItem(this);
}

QString StaticItem::editorRelativePath(QString fileName)
{
	return STATIC_DIR + fileName + ".png";
}


