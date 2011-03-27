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
	virtual void addToData(Data *data, bool push_front = true) = 0;
	virtual void edit();
	virtual void moveItem(int x, int y);
	virtual void setPos(int x, int y);
	virtual MyItem* selectItem(int x, int y);
	
};



#endif
