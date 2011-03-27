#include "platformitem.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "paths.h"
#include <QGraphicsScene>
#include <QInputDialog>

PlatformItem::PlatformItem(QGraphicsPixmapItem *item, QString fileName, PlatformItem *father):
	StaticItem(item, fileName),
	m_father(father),
	m_son(NULL)
{
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		QPixmap image(m_item->pixmap()); // on duplique l'image pour le fils
		this->setSon(new PlatformItem(m_item->scene()->addPixmap(image), fileName, this)); // felicitations, c'est un garcon!
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

MyItem *PlatformItem::duplicate()
{
	// TODO 
	QPixmap image(m_item->pixmap());
	PlatformItem *item = new PlatformItem(m_item->scene()->addPixmap(image), m_file_name);
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
