#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsPixmapItem>

class Data;
class QGraphicsPixmapItem;

class MyItem {
	protected:
	QGraphicsPixmapItem *m_item;
	QString m_file_name;
	public:
	MyItem(QGraphicsPixmapItem *item, QString);
	~MyItem();
	virtual MyItem *duplicate() = 0;
	QGraphicsPixmapItem *getItem();
	virtual void saveItem(QTextStream &out) = 0;
	virtual void addToData(Data *data) = 0;
	virtual void edit();
	
};



#endif