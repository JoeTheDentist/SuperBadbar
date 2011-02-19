#include "data.h"
#include "myitem.h"
#include <iostream>

Data::Data():
	m_items(),
	m_background(NULL),
	m_xpix(0),
	m_ypix(0)
{
	
}

Data::~Data()
{
	// Ne pas détruire les items!! MyGraphicsView le fera automatiquement
}

void Data::setBackground(MyItem *item)
{
	m_background = item;
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
	// les items doivent si possible etre tries par ordre d'ajout	
	// cet ordre ne sera que partiellement garde apres sauvegarde et rechargement
	// du .lvl: les items de meme type resteront triés entre eux
	m_items.push_front(item);
}

void Data::saveData(QString fileName)
{
	std::cout << "Saving " << std::endl;
}
