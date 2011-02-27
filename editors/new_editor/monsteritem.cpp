#include <QGraphicsItem>
#include <iostream>
#include "monsteritem.h"
#include "paths.h"
#include <QFile>
#include "analyser.h"

MonsterItem::MonsterItem(QGraphicsItem *item, QString fileName):
	MyItem(item, fileName),
	m_class_name("")
{
	Analyser analyser;
	analyser.open((MONSTERS_DIR + fileName + ".mstr").toStdString());
	m_class_name = QString::fromStdString(analyser.read_string());
}                

MonsterItem::~MonsterItem()
{
	
}

void MonsterItem::saveItem(QTextStream &out)
{
	out << m_class_name << " " << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
}

void MonsterItem::addToData(Data *data)
{
	data->addMonsterItem(this);
}

QString MonsterItem::picPathFromEditor(QString fileName)
{
	return MONSTERS_PIC_DIR + fileName + "/" + fileName + "_0_0_0.png";
}


