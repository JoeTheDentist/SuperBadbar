#include "staticitem.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "paths.h"
#include <QGraphicsScene>
#include <QInputDialog>

StaticItem::StaticItem(QGraphicsPixmapItem *item, QString fileName, int buffer):
	MyItem(item, fileName),
	m_zbuffer(buffer)
{
	
}

StaticItem::~StaticItem()
{
	
}

MyItem *StaticItem::duplicate()
{
	QPixmap image(m_item->pixmap());
	StaticItem *item = new StaticItem(m_item->scene()->addPixmap(image), m_file_name);
	item->getItem()->setVisible(false);
	item->m_zbuffer = m_zbuffer;
	return item;	
}


void StaticItem::saveItem(QTextStream &out)
{
	out << m_file_name << " " << m_item->x() << " " << m_item->y() << " " << m_zbuffer << endl;
}

void StaticItem::addToData(Data *data)
{
	data->addStaticItem(this);
}




void StaticItem::edit()
{
	int entier = QInputDialog::getInteger(NULL, "ZBuffer", "Entrez le niveau de zbuffer (0 ou 1)");
	if (entier <= 0) {
		setStaticZBuffer(0);
	} else {
		setStaticZBuffer(1);
	}
}


QString StaticItem::picPathFromEditor(QString fileName)
{
	return STATIC_DIR + fileName + ".png";
}

void StaticItem::setStaticZBuffer(int buffer)
{
	m_zbuffer = buffer;
	if (m_zbuffer == 0) {
		this->getItem()->setZValue(STATICS_0_ZBUFFER);
	} else {
		this->getItem()->setZValue(STATICS_1_ZBUFFER);
	}
}
