#include "platformitem.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "paths.h"
#include "mygraphicsview.h"
#include <QGraphicsScene>
#include <QInputDialog>
#include <QStringList>

PlatformItem::PlatformItem(QGraphicsScene *scene, QString fileName, PlatformItem *father):
	StaticItem(scene, fileName),
	m_father(father),
	m_son(NULL),
	m_nature("normal")
{
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		this->setSon(new PlatformItem(scene, fileName, this)); // felicitations, c'est un garcon!
	}
}

PlatformItem::PlatformItem(QGraphicsScene *scene, QString fileName, Analyser &analyser, PlatformItem *father):
	StaticItem(scene, fileName),
	m_father(father),
	m_son(NULL),
	m_nature("normal")
{
	if (isFather())
		setNature(QString(analyser.read_string().c_str()));
	int x = analyser.read_int();
	int y = analyser.read_int();
	setPos(x, y);
	if (!father) { // si aucun pere n'est precise, c'est qu'on EST le pere
		this->setSon(new PlatformItem(scene, fileName, analyser, this)); // felicitations, c'est un garcon!
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
	if (isFather()) {
		QPixmap image(m_item->pixmap());
		PlatformItem *item = new PlatformItem(scene, m_file_name);
		item->m_son->moveItem(m_son->x() - x(), m_son->y() - y()); // on maintient le decalage
		item->setVisible(false); 
		item->m_zbuffer = m_zbuffer;
		item->setNature(m_nature);
		return item;	
	} else {
		return m_father->duplicate(scene);
	}
}

void PlatformItem::saveItem(QTextStream &out)
{
	if (isFather()) {
		out << m_nature << " " << m_file_name << " " << m_item->x() << " " << m_item->y() << " ";
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
	QStringList choices;
    choices << "normal" << "falling";
    setNature(QInputDialog::getItem(NULL, "Plaform nature", "Indicate the nature of the platform", choices));
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

void PlatformItem::removeFromScene(QGraphicsScene *scene)
{
	if (isFather()) {
		scene->removeItem(m_son->getItem());
		MyItem::removeFromScene(scene);
	}
}

void PlatformItem::setVisible(bool visible)
{
	if (isFather())
		m_son->setVisible(visible);
	MyItem::setVisible(visible);
}

void PlatformItem::setNature(QString nature)
{
	m_nature = nature;
	if (isFather())
		m_son->m_nature = nature;
	else
		m_father->m_nature = nature;
}
