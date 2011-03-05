#include <QGraphicsPixmapItem>
#include <iostream>
#include "eventitem.h"
#include "paths.h"
#include <QFile>
#include "analyser.h"
#include <QGraphicsScene>

EventItem::EventItem(QGraphicsPixmapItem *item, QString fileName):
	MyItem(item, fileName),
	m_class_name("")
{
	m_class_name = "event";
}                

EventItem::~EventItem()
{
	
}

MyItem *EventItem::duplicate()
{
	QPixmap image(m_item->pixmap());
	MyItem *item = new EventItem(m_item->scene()->addPixmap(image), m_file_name);
	item->getItem()->setVisible(false);
	return item;
}

void EventItem::saveItem(QTextStream &out)
{
	out << m_class_name << " " << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
}

void EventItem::addToData(Data *data)
{
	data->addEventItem(this);
}

QString EventItem::picPathFromEditor(QString fileName)
{
	Analyser analyser;
	analyser.open(EVENTS_DIR + fileName.toStdString() + EVENTS_EXT);
	if (analyser.find_string("#picture#")) {
		return EVENTS_PIC_DIR + fileName + ".png";
	} else {
		std::cout << "Pas d'image pour cet événement, erreur" << std::endl;
		return "";
	}
}
