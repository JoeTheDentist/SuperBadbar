#include <QGraphicsItem>
#include <iostream>
#include <QFile>
#include <QGraphicsScene>

#include <items/EventItem.h>
#include <util/paths.h>
#include <util/Analyser.h>

EventItem::EventItem(QGraphicsScene *scene, QString fileName):
	MyItem(NULL, fileName),
	m_class_name("")
{
	QPixmap image;
	image.load(EventItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	m_class_name = "event";
}                


EventItem::~EventItem()
{
	
}

MyItem *EventItem::duplicate(QGraphicsScene *scene)
{
	MyItem *item = new EventItem(scene, m_file_name);
	item->getItem()->setVisible(false);
	return item;
}

void EventItem::saveItem(QTextStream &out)
{
	out << m_class_name << " " << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
}

void EventItem::addToData(Data *data, bool push_front)
{
	data->addEventItem(this, push_front);
}

QString EventItem::picPathFromEditor(QString fileName)
{
	Analyser analyser;
	analyser.open(EVENTS_DIR + fileName.toStdString() + EVENTS_EXT);

	if (analyser.find_string("#picture#")) {
		return QString::fromStdString(EVENTS_PIC_DIR + analyser.read_string());
	} else {
		std::cout << "Pas d'image pour cet événement, erreur" << std::endl;
		return "";
	}
}
