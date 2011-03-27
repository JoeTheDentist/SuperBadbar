#include <QGraphicsPixmapItem>
#include <iostream>
#include "monsteritem.h"
#include "paths.h"
#include <QFile>
#include "analyser.h"
#include <QGraphicsScene>



MonsterItem::MonsterItem(QGraphicsScene *scene, QString fileName):
	MyItem(NULL, fileName),
	m_class_name("")
{
	QPixmap image;
	image.load(MonsterItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	Analyser analyser;
	analyser.open((MONSTERS_DIR + fileName + ".mstr").toStdString());
	analyser.find_string("#Class#");
	m_class_name = QString::fromStdString(analyser.read_string());
}      

MonsterItem::~MonsterItem()
{
	
}

MyItem *MonsterItem::duplicate(QGraphicsScene *scene)
{
	MyItem *item = new MonsterItem(scene, m_file_name);
	item->getItem()->setVisible(false);
	return item;
}



void MonsterItem::saveItem(QTextStream &out)
{
	out << m_class_name << " " << m_file_name << " " << (int)m_item->x() << " " << (int)m_item->y() << endl;
}

void MonsterItem::addToData(Data *data, bool push_front)
{
	data->addMonsterItem(this, push_front);
}

QString MonsterItem::picPathFromEditor(QString fileName)
{
	return MONSTERS_PIC_DIR + fileName + "/" + fileName + "_0_0_0.png";
}


