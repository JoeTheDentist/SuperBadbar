//~ #include "staticitem.h"
//~ #include <QGraphicsItem>
//~ #include <iostream>
//~ #include "monsters.h"

//~ MonsterItem::MonsterItem(QGraphicsItem *item, QString fileName):
//~ 	MyItem(item, fileName),
//~ 	m_class_name("")
//~ {
//~ 	// TROUVER CLASS_NAME
//~ }                

//~ MonsterItem::~MonsterItem()
//~ {
//~ 	
//~ }

//~ void MonsterItem::saveItem(QTextStream &out)
//~ {
//~ 	out << m_file_name << " " << m_item->x() << " " << m_item->y() << " " << 0 << endl;
//~ }

//~ void MonsterItem::addToData(Data *data)
//~ {
//~ 	data->addMonsterItem(this);
//~ }

//~ QString MonsterItem::editorRelativePath(QString fileName)
//~ {
//~ 	return MONSTER_DIR + fileName + ".png";
//~ }


