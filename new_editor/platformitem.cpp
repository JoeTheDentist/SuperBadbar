#include "platformitem.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "paths.h"
#include "mygraphicsview.h"
#include <QGraphicsScene>
#include <QInputDialog>

PlatformItem::PlatformItem(QGraphicsScene *scene, QString fileName, PlatformItem *father):
	StaticItem(scene, fileName),
	m_father(father),
	m_son(NULL)
{
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		this->setSon(new PlatformItem(scene, fileName, this)); // felicitations, c'est un garcon!
	}
}



PlatformItem::~PlatformItem()
{
	if (isFather())
		delete m_son;
}

void PlatformItem::setFather(PlatformItem *father)
{
	m_father = father;
}

void PlatformItem::setSon(PlatformItem *son)
{
	m_son = son;
	son->setFather(this);
}

MyItem *PlatformItem::duplicate(QGraphicsScene *scene)
{
	// TODO 
	QPixmap image(m_item->pixmap());
	PlatformItem *item = NULL; //new PlatformItem(m_item->scene()->addPixmap(image), m_file_name);
	item->getItem()->setVisible(false);
	item->m_zbuffer = m_zbuffer;
	return item;	
}

void PlatformItem::saveItem(QTextStream &out)
{
	if (isFather()) {
		out << m_file_name << " " << m_item->x() << " " << m_item->y() << " ";
		m_son->saveItem(out);
	} else {
		out << m_item->x() << " " << m_item->y() << endl;
	}
}

void PlatformItem::addToData(Data *data, bool push_front)
{
	if (isFather()) // on ne doit jamais ajouter un fils dans data
		data->addPlatformItem(this, push_front);
}

void PlatformItem::edit()
{
	// TODO
	int entier = QInputDialog::getInteger(NULL, "ZBuffer", "Entrez le niveau de zbuffer (0 ou 1)");
	if (entier <= 0) {
		setStaticZBuffer(0);
	} else {
		setStaticZBuffer(1);
	}
}

QString PlatformItem::picPathFromEditor(QString fileName)
{
	return STATIC_DIR + fileName + ".png";
}

void PlatformItem::moveItem(int x, int y)
{
	StaticItem::moveItem(x, y);
	if (isFather()) {
		m_son->moveItem(x, y);
	} else {
	}
}

void PlatformItem::setPos(int x, int y)
{
	StaticItem::setPos(x, y);
	if (isFather()) {
		m_son->setPos(x, y);
	} else {
	}
}

void PlatformItem::setStaticZBuffer(int buffer)
{
	m_zbuffer = buffer;
	if (m_zbuffer == 0) {
		this->getItem()->setZValue(STATICS_0_ZBUFFER);
	} else {
		this->getItem()->setZValue(STATICS_1_ZBUFFER);
	}
	if (isFather()) {
		m_son->setStaticZBuffer(buffer);
	}
}

MyItem *PlatformItem::selectItem(int x, int y)
{
	if (isFather()) {
		if (m_son->selectItem(x, y))
			return m_son->selectItem(x, y);
	}
	QGraphicsPixmapItem *item = this->getItem();
	if (item->x() <= x && x <= item->x() + item->boundingRect().width()
		&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {	
		return this;	
	}
	return NULL;
}

