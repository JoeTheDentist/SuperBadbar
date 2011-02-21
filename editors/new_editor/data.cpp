#include "data.h"
#include "myitem.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QGraphicsItem>

Data::Data():
	m_static_items(),
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

void Data::setBackground(QGraphicsItem *item, QString filename)
{
	m_background = item;
	m_background_name = filename.right(filename.size() - (filename.lastIndexOf("backgrounds/") + 12));
	m_xpix = item->boundingRect().width();
	m_ypix = item->boundingRect().height();
	//TODO il faudra faire d'autres traitements
}

void Data::setLevelSize(int x, int y)
{
	m_xpix = x;
	m_ypix = y;
	// TODO il faudra faire d'autres traitements
}

void Data::addItem(MyItem *item)
{
	item->addToData(this);
}

void Data::addStaticItem(MyItem *item)
{
	// les items doivent si possible etre tries par ordre d'ajout	
	// cet ordre ne sera que partiellement garde apres sauvegarde et rechargement
	// du .lvl: les items de meme type resteront triés entre eux
	m_static_items.push_front(item);
	
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
	out << 300 << endl; // TODO
	out << 300 << endl;
	out << 1 << endl;
	out << endl;
	// sauvegarde des statics TODO 
	out << "#Statics#" << endl;
	out << m_static_items.size() << endl;
	for (it = m_static_items.begin(); it != m_static_items.end(); it++)
		(*it)->saveItem(out);
	out << endl;
	
	// sauvegarde des monstres TODO 
	
	// sauvegarde des events TODO 
	
	file.close();
}

MyItem *Data::selectItem(int x, int y)
{
	std::list<MyItem *>::iterator it;
	QGraphicsItem *item;
	for (it = m_static_items.begin(); it != m_static_items.end(); it++) {
		item = (*it)->getItem();
		if (item->x() <= x && x <= item->x() + item->boundingRect().width()
			&& item->x() <= x && x <= item->x() + item->boundingRect().width()) {
			return (*it);	
		}
	}
	return NULL;
	
}
