#include "data.h"
#include "myitem.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QGraphicsItem>
#include "paths.h"

Data::Data():
	m_static_items(),
	m_monsters_items(),
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
	image.load(backgroundName, 0, Qt::AutoColor);
	m_background_name = backgroundName.right(backgroundName.size() - (backgroundName.lastIndexOf("backgrounds/") + 12));
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

void Data::addItem(MyItem *item)
{
	item->addToData(this);
}

void Data::addStaticItem(MyItem *item)
{
	m_static_items.push_front(item);
}
void Data::addMonsterItem(MyItem *item)
{
	m_monsters_items.push_front(item);
}

MyItem *Data::selectItem(int x, int y)
{
	std::list<MyItem *>::iterator it;
	QGraphicsItem *item;
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {
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
	return NULL;
	
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
	out << m_background_name << endl << endl;
	// sauvegarde de la taile du niveau  
	out << "#Level_dimensions#" << endl;
	out << m_xpix << endl;
	out << m_ypix << endl;
	out << endl;
	// sauvegarde de la position de départ de babar 
	out << "#Babar#" << endl;
	out << 300 << endl; // 
	out << 300 << endl;
	out << 1 << endl;
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
	// sauvegarde des events TODO 
	out << "#Events#" << endl;
	out << 0 << endl;
	out << "!" << endl;
	file.close();
}

void Data::removeItem(MyItem *item)
{
	std::list<MyItem *>::iterator it;
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {	
		if (item == (*it)) {
			m_static_items.erase(it);
			return;
		}
	}
}


