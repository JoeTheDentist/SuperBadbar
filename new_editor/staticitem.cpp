#include "staticitem.h"
#include <QGraphicsItem>
#include <iostream>
#include "paths.h"
#include <QGraphicsScene>
#include <QInputDialog>

StaticItem::StaticItem(QGraphicsScene *scene, QString fileName, int buffer):
	MyItem(NULL, fileName),
	m_zbuffer(buffer)
{
	QPixmap image;
	image.load(StaticItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
}

StaticItem::~StaticItem()
{
	
}

MyItem *StaticItem::duplicate(QGraphicsScene *scene)
{
	StaticItem *item = new StaticItem(scene, m_file_name);
	item->getItem()->setVisible(false);
	item->m_zbuffer = m_zbuffer;
	return item;	
}


void StaticItem::saveItem(QTextStream &out)
{
	out << m_file_name << " " << m_item->x() << " " << m_item->y() << " " << m_zbuffer << endl;
}

void StaticItem::addToData(Data *data, bool push_front)
{
	data->addStaticItem(this, push_front);
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
