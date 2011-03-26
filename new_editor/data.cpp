#include "data.h"
#include "myitem.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QGraphicsPixmapItem>
#include "paths.h"

Data::Data():
	m_babar_item(NULL),
	m_static_items(),
	m_monsters_items(),
	m_event_items(),
	m_background_name(""),
	m_background(NULL),
	m_xpix(0),
	m_ypix(0)
{
	
}

Data::~Data()
{
	// Ne pas détruire les items!! MyGraphicsView le fera automatiquement
}

void Data::initData(QString backgroundName)
{
	
	QPixmap image;
	std::cout << backgroundName.toStdString() << " " ;
	m_background_name = backgroundName.right(backgroundName.size() - (backgroundName.lastIndexOf("backgrounds/") + 12));
	image.load(BACKGROUND_DIR + m_background_name, 0, Qt::AutoColor);
	std::cout << m_background_name.toStdString() << std::endl;
	m_xpix = image.width() * 2 - CAMERA_WIDTH;
	m_ypix = image.height() * 2 - CAMERA_HEIGHT;
}

int Data::levelWidth()
{
	return m_xpix;
}

int Data::levelHeight()
{
	return m_ypix;
}

void Data::addItem(MyItem *item, bool push_front)
{
	item->addToData(this, push_front);
}

void Data::addBabarItem(MyItem *item)
{
	m_babar_item = item;
	item->getItem()->setZValue(BABAR_ZBUFFER);	
}

void Data::addStaticItem(MyItem *item, bool push_front)
{
	if (push_front) {
		m_static_items.push_front(item);		
	} else {
		m_static_items.push_back(item);
	}
	item->getItem()->setZValue(STATICS_0_ZBUFFER);
}

void Data::addMonsterItem(MyItem *item, bool push_front)
{	
	if (push_front) {
		m_monsters_items.push_front(item);		
	} else {
		m_monsters_items.push_back(item);
	}
	item->getItem()->setZValue(MONSTERS_ZBUFFER);	
}


void Data::addEventItem(MyItem *item, bool push_front)
{
	if (push_front) {
		m_event_items.push_front(item);		
	} else {
		m_event_items.push_back(item);
	}
	item->getItem()->setZValue(EVENTS_ZBUFFER);	
}



MyItem *Data::selectItem(int x, int y)
{
	std::list<MyItem *>::iterator it;
	QGraphicsPixmapItem *item;
	item = m_babar_item->getItem();
	if (item->x() <= x && x <= item->x() + item->boundingRect().width()
		&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {	
		return m_babar_item;	
	}
	for (it = m_event_items.begin(); it != m_event_items.end(); it++) {
		item = (*it)->getItem();
		if (item->x() <= x && x <= item->x() + item->boundingRect().width()
			&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {
			return (*it);	
		}
	}
	for (it = m_monsters_items.begin(); it != m_monsters_items.end(); it++) {
		item = (*it)->getItem();
		if (item->x() <= x && x <= item->x() + item->boundingRect().width()
			&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {
			return (*it);	
		}
	}
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {
		item = (*it)->getItem();
		if (item->x() <= x && x <= item->x() + item->boundingRect().width()
			&& item->y() <= y && y <= item->y() + item->boundingRect().height()) {
			return (*it);	
		}
	}
	return NULL;
}

MyItem *Data::selectBabar()
{
	return m_babar_item;
}

void Data::deleteItem(MyItem *item)
{
	std::list<MyItem *>::iterator it;
 	for (it = m_event_items.begin(); it != m_event_items.end();it++) {
		if (*it == item) {
			m_event_items.erase(it);
			return;
		}
	}
	for (it = m_monsters_items.begin(); it != m_monsters_items.end();it++) {
		if (*it == item) {
			m_monsters_items.erase(it);
			return;
		}
	}
	for (it = m_static_items.begin(); it != m_static_items.end();it++) {
		if (*it == item) {
			m_static_items.erase(it);
			return;
		}
	}
}

void Data::upInStack(MyItem *item) 
{
	std::list<MyItem *>::iterator it;
 	for (it = m_event_items.begin(); it != m_event_items.end(); it++) {
 		(*it)->getItem()->stackBefore(item->getItem());
	}
	for (it = m_monsters_items.begin(); it != m_monsters_items.end(); it++) {
		(*it)->getItem()->stackBefore(item->getItem());
	}
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {
 		(*it)->getItem()->stackBefore(item->getItem());
	}	
	deleteItem(item);
	addItem(item, false);
}

void Data::saveData(QString fileName)
{

	std::cout << "Saving " << std::endl;
	QFile file(fileName);
	std::list<MyItem *>::iterator it;
	file.open( QIODevice::WriteOnly | QIODevice::Text );
	QTextStream out(&file);
	// sauvegarde du background  
	out << "#Background#" << endl;
	std::cout << m_background_name.toStdString() << std::endl;
	out << m_background_name << endl << endl;
	// sauvegarde de la taile du niveau  
	out << "#Level_dimensions#" << endl;
	out << m_xpix << endl;
	out << m_ypix << endl;
	out << endl;
	// sauvegarde de la position de départ de babar 
	out << "#Babar#" << endl;
	m_babar_item->saveItem(out);
	out << endl;
	// sauvegarde des statics  
	out << "#Statics#" << endl;
	out << m_static_items.size() << endl;	
	for (it = m_static_items.begin(); it != m_static_items.end(); it++)
		(*it)->saveItem(out);
	out << "!" << endl;
	// sauvegarde des monsters 
	out << "#Monsters#" << endl;
	out << m_monsters_items.size() << endl;
	for (it = m_monsters_items.begin(); it != m_monsters_items.end(); it++)
		(*it)->saveItem(out);
	out << "!" << endl;
	// sauvegarde des events  
	out << "#Events#" << endl;
	out << m_event_items.size() << endl;
	for (it = m_event_items.begin(); it != m_event_items.end(); it++)
		(*it)->saveItem(out);	
	out << "!" << endl;
	// sauvegarde des plateformes
	out << "#Plateforms#" << endl;
	out << "0" << endl;
	out << "!" << endl;
	out << "#Anims#" << endl;
	out << "0" << endl;
	out << "!" << endl;
	file.close();	
	
}

void Data::removeItem(MyItem *item)
{
	std::list<MyItem *>::iterator it;
	
	for (it = m_event_items.begin(); it != m_event_items.end(); it++) {	
		if (item == (*it)) {
			m_event_items.erase(it);
			return;
		}
	}	
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {	
		if (item == (*it)) {
			m_static_items.erase(it);
			return;
		}
	}
	for (it = m_monsters_items.begin(); it != m_monsters_items.end(); it++) {	
		if (item == (*it)) {
			m_monsters_items.erase(it);
			return;
		}
	}
}


