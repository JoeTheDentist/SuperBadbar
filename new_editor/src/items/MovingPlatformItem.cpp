#include "MovingPlatformItem.h"

#include <QGraphicsItem>
#include <iostream>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QStringList>

#include <util/paths.h>
#include <editor/MyGraphicsView.h>


MovingPlatformItem::MovingPlatformItem(QGraphicsScene *scene, QString fileName, MovingPlatformItem *father):
	StaticItem(scene, fileName),
	m_father(father),
	m_son(NULL)
{
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		this->setSon(new MovingPlatformItem(scene, fileName, this)); // felicitations, c'est un garcon!
	}
}

MovingPlatformItem::MovingPlatformItem(QGraphicsScene *scene, QString fileName, Analyser &analyser, MovingPlatformItem *father):
	StaticItem(scene, fileName),
	m_father(father),
	m_son(NULL)
{
	int x = analyser.read_int();
	int y = analyser.read_int();
	setPos(x, y);
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		this->setSon(new MovingPlatformItem(scene, fileName, analyser, this)); // felicitations, c'est un garcon!
	}
}

MovingPlatformItem::~MovingPlatformItem()
{
	if (isFather())
		delete m_son;
}

void MovingPlatformItem::setFather(MovingPlatformItem *father)
{
	m_father = father;
}

void MovingPlatformItem::setSon(MovingPlatformItem *son)
{
	m_son = son;
	son->setFather(this);
}

MyItem *MovingPlatformItem::duplicate(QGraphicsScene *scene)
{
	if (isFather()) {
		MovingPlatformItem *item = new MovingPlatformItem(scene, m_file_name);
		item->m_son->moveItem(m_son->x() - x(), m_son->y() - y()); // on maintient le decalage
		item->setVisible(false); 
		item->m_zbuffer = m_zbuffer;
		return item;	
	} else {
		return m_father->duplicate(scene);
	}
}

void MovingPlatformItem::saveItem(QTextStream &out)
{
	if (isFather()) {
		out << m_file_name << " " << m_item->x() << " " << m_item->y() << " ";
		m_son->saveItem(out);
	} else {
		out << m_item->x() << " " << m_item->y() << endl;
	}
}

void MovingPlatformItem::addToData(Data *data, bool push_front)
{
	if (isFather()) // on ne doit jamais ajouter un fils dans data
		data->addMovingPlatformItem(this, push_front);
}

void MovingPlatformItem::edit()
{
}

QString MovingPlatformItem::picPathFromEditor(QString fileName)
{
	return STATIC_DIR + fileName + ".png";
}

void MovingPlatformItem::moveItem(int x, int y)
{
	qWarning("plop");
	StaticItem::setPos(this->getItem()->x() + x, this->getItem()->y() + y);
	if (isFather()) {
		m_son->moveItem(x, y);
	} else {
	}
}

void MovingPlatformItem::setPos(int x, int y)
{
	StaticItem::setPos(x, y);
	if (isFather()) {
		m_son->setPos(x, y);
	} else {
	}
}

void MovingPlatformItem::setStaticZBuffer(int buffer)
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

MyItem *MovingPlatformItem::selectItem(int x, int y)
{
	if (isFather()) {
		if (m_son->selectItem(x, y))
			return m_son->selectItem(x, y);
	}
	QGraphicsItem *item = this->getItem();
	if (item->x() <= x && x <= item->x() + item->boundingRect().width()
		&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {	
		return this;	
	}
	return NULL;
}

void MovingPlatformItem::removeFromScene(QGraphicsScene *scene)
{
	if (isFather()) {
		scene->removeItem(m_son->getItem());
		MyItem::removeFromScene(scene);
	}
}

void MovingPlatformItem::setVisible(bool visible)
{
	if (isFather())
		m_son->setVisible(visible);
	MyItem::setVisible(visible);
}


