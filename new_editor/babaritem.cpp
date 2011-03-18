#include "babaritem.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "paths.h"
#include <QGraphicsScene>
#include <QInputDialog>

BabarItem::BabarItem(QGraphicsPixmapItem * item, int age):
	MyItem(item, QString(BABAR_PIC_DIR) + "1/babar_0_0_0.png"),
	m_age(age)
{
	
}

BabarItem::~BabarItem()
{
	
}

MyItem *BabarItem::duplicate()
{
	return this;	
}


void BabarItem::saveItem(QTextStream &out)
{
	out << m_item->x() << endl << m_item->y() << endl << m_age << endl;
}

void BabarItem::addToData(Data *data, bool push_front)
{
	push_front = false; // ne fait rien ;)
	data->addBabarItem(this);
}

void BabarItem::edit()
{
	int entier = QInputDialog::getInteger(NULL, "Age", "Entrez l'age de Babar (1 à 3)");
	if (entier <= 1) {
		setBabarAge(1);       
	} else if (entier > 3) {
		setBabarAge(3);
	} else {
		setBabarAge(entier);
	}	
}

QString BabarItem::picPathFromEditor(QString fileName)
{
	return "images/" + fileName + ".png";
}

void BabarItem::setBabarAge(int entier)
{
	m_age = entier;
}
