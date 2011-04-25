#include "fallingplatformitem.h"
#include "paths.h"
FallingPlatformItem::FallingPlatformItem(QGraphicsScene *scene, QString fileName, int buffer):
	StaticItem(scene, fileName, buffer)
{
	
}

MyItem *FallingPlatformItem::duplicate(QGraphicsScene *scene)
{
	FallingPlatformItem *item = new FallingPlatformItem(scene, m_file_name);
	item->getItem()->setVisible(false);
	item->m_zbuffer = m_zbuffer;
	return item;	
}

void FallingPlatformItem::saveItem(QTextStream &out)
{
	out << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
}

void FallingPlatformItem::addToData(Data *data, bool push_front)
{
	data->addFallingPlatformItem(this, push_front);
}

QString FallingPlatformItem::picPathFromEditor(QString fileName)
{
	return STATIC_DIR + fileName + ".png";
}
