#include <QGraphicsPixmapItem>
#include <iostream>
#include "zoneitem.h"
#include "triggeritem.h"
#include "mygraphicsview.h"
#include "utils.h"
#include <QFile>
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QWidget>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>



ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, int x, int y, int w, int h):
	MyItem(NULL, ""),
	m_parent(parent)
{
	m_width = w;
	m_height = h;
	setItem(scene->addRect(0, 0, m_width, m_height));
	setPos(x, y);
}                

ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser):
	MyItem(NULL, ""),
	m_parent(parent)
{
	int x, y;
	x = analyser.read_int();
	y = analyser.read_int();
	m_width = analyser.read_int() - x;
	m_height = analyser.read_int() - y;
	setItem(scene->addRect(0, 0, m_width, m_height));
	setPos(x, y);
}

ZoneItem::~ZoneItem()
{
	
}

MyItem *ZoneItem::duplicate(QGraphicsScene *scene)
{
//~ 	MyItem *item = new ZoneItem(scene, QString("../data/level/" + m_level_name + ".lvl"));
//~ 	item->getItem()->setVisible(false);
//~ 	return item;
	return NULL;
}

void ZoneItem::saveItem(QTextStream &out)
{
	out << x() << " " << y() << " " << x() + m_width << " " << y() + m_height << endl;
}

void ZoneItem::addToData(Data *data, bool push_front)
{
	std::cout << "add to data position " << std::endl;
	m_parent->addZoneItem(this);
}

QString ZoneItem::picPathFromEditor(QString fileName)
{
	fileName = ""; //unused param
	return QString::fromStdString("../new_editor/images/triggerable.png");
}

void ZoneItem::edit()
{
}

void ZoneItem::moveItem(int xrel, int yrel, int xabs, int yabs)
{
	if (m_state == e_beingResized) {
		changeCoordinates(x(), y(), xabs, yabs);
	} else {
		MyItem::moveItem(xrel, yrel, xabs, yabs);
		changeCoordinates(x(), y(), m_width + x(), m_height + y());
	}
}

void ZoneItem::signalEndOfAdding()
{
	std::cout << "signal" << std::endl;
	if (m_state == e_beingAdded) {
		m_view->setStateAddingItem(this);
		m_state = e_beingResized;
	} else {
		MyItem::signalEndOfAdding();
	}

}

void ZoneItem::changeCoordinates(int x, int y, int x2, int y2) 
{
	m_width = x2- this->x();
	m_height = y2 - this->y();
	removeFromScene(m_view->scene());
	setItem(m_view->scene()->addRect(0, 0, m_width, m_height));
	setPos(x, y);
	
}
