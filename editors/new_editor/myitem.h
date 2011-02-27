#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsPixmapItem>

class Data;
class QGraphicsItem;

class MyItem {
	protected:
	QGraphicsItem *m_item;
	QString m_file_name;
	public:
	MyItem(QGraphicsItem *item, QString);
	MyItem(const MyItem &item);
	~MyItem();
	QGraphicsItem *getItem();
	virtual void saveItem(QTextStream &out);
	virtual void addToData(Data *data) = 0;
	
};



#endif
