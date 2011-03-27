#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Data;
class QGraphicsPixmapItem;

class MyItem {
	protected:
	QGraphicsPixmapItem *m_item;
	QString m_file_name;
	public:
	MyItem(QGraphicsPixmapItem *item, QString);
	~MyItem();
	virtual MyItem *duplicate(QGraphicsScene *scene) = 0;
	QGraphicsPixmapItem *getItem();
	int x() {return m_item->x();}
	int y() {return m_item->y();}
	virtual void saveItem(QTextStream &out) = 0;
	virtual void addToData(Data *data, bool push_front = true) = 0;
	virtual void edit();
	virtual void moveItem(int x, int y);
	virtual void setPos(int x, int y);
	virtual MyItem* selectItem(int x, int y);
	virtual void removeFromScene(QGraphicsScene *scene);
	virtual void setVisible(bool visible) { m_item->setVisible(visible);}
	
	protected:
	void setItem(QGraphicsPixmapItem *item) { m_item = item; }
	
};



#endif
