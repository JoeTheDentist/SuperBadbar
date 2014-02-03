#include "ZoneItem.h"

#include <QGraphicsPixmapItem>
#include <iostream>
#include <QFile>
#include <QGraphicsScene>
#include <QWidget>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>

#include <editor/MainWindow.h>
#include <editor/MyGraphicsView.h>
#include <items/TriggerItem.h>
#include <util/utils.h>

ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, int x, int y, int w, int h):
	MyItem(NULL, ""),
	m_parent(parent)
{
	Q_UNUSED(scene);
	m_width = w;
	m_height = h;
	setItem(addRect(0, 0, m_width, m_height));
	setPos(x, y);
}                

ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser):
	MyItem(NULL, ""),
	m_parent(parent)
{
	Q_UNUSED(scene);
	int x, y;
	x = analyser.read_int();
	y = analyser.read_int();
	m_width = analyser.read_int() - x;
	m_height = analyser.read_int() - y;
	setItem(addRect(0, 0, m_width, m_height));
	setPos(x, y);
}

ZoneItem::ZoneItem(ZoneItem &original):
	MyItem(NULL, "", e_beingAdded),
	m_parent(original.m_parent),
	m_width(original.m_width),
	m_height(original.m_height)
{
	setItem(addRect(0, 0, m_width, m_height));
	setPos(original.x(), original.y());	
}


ZoneItem::~ZoneItem()
{
	
}

MyItem *ZoneItem::duplicate(QGraphicsScene *scene)
{
	Q_UNUSED(scene);
	MyItem *newitem = new ZoneItem(*this);
	newitem->getItem()->setVisible(false);
	return newitem;
}

void ZoneItem::saveItem(QTextStream &out)
{
	out << x() << " " << y() << " " << x() + m_width << " " << y() + m_height << endl;
}

void ZoneItem::addToData(Data *data, bool push_front)
{
	Q_UNUSED(data);
	Q_UNUSED(push_front);
	m_parent->addZoneItem(this);
}

QString ZoneItem::picPathFromEditor(QString fileName)
{
	fileName = ""; //unused param
	return QString::fromStdString("../new_editor/images/triggerable.png");
}

void ZoneItem::edit()
{
	m_view->setStateAddingItem(this);
	m_state = e_beingResized;	
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
	// si le rectangle est a l'envers, on le remet a l'endroit
	if (m_width < 0) {
		m_width = -m_width;
		setPos(x() -m_width, y());
	}
	if (m_height < 0) {
		m_height = -m_height;
		setPos(x(), y() - m_height);
	}
	int x1 = x();
	int y1 = y();
	removeFromScene(m_view->scene());
	setItem(addRect(0, 0, m_width, m_height));
	setPos(x1, y1);

}

void ZoneItem::changeCoordinates(int x, int y, int x2, int y2) 
{
	m_width = x2- this->x();
	m_height = y2 - this->y();
	removeFromScene(m_view->scene());
	setItem(addRect(0, 0, m_width, m_height));
	setPos(x, y);
	
}

QGraphicsItem *ZoneItem::addRect(int x1, int y1, int w, int h)
{
	if (w < 0) {
		w = -w;
		x1 -=w;
	}
	if (h < 0) {
		h = -h;
		y1 -=h;
	}
	return m_view->scene()->addRect(x1, y1, w, h);
}
