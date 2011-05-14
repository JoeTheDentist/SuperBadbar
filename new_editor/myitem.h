#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <iostream>

class Data;
class QGraphicsPixmapItem;
class MyGraphicsView;

class MyItem {
	protected:
	static MyGraphicsView *m_view;
	QGraphicsPixmapItem *m_item;
	QString m_file_name;
	public:
	MyItem(QGraphicsPixmapItem *item, QString);
	~MyItem();
	static void setView(MyGraphicsView *view);
	static MyGraphicsView *getView();
	virtual MyItem *duplicate(QGraphicsScene *scene) = 0;
	QGraphicsPixmapItem *getItem();
	int x() {return m_item->x();}
	int y() {return m_item->y();}
	virtual void saveItem(QTextStream &out) = 0;
	virtual void addToData(Data *data, bool push_front = true) = 0;
	virtual void edit();
	virtual void rightClic(int x, int y) { x = 0; y = 0; std::cout << "right clic" << std::endl; }
	virtual void moveItem(int x, int y);
	virtual void setPos(int x, int y);
	virtual MyItem* selectItem(int x, int y);
	virtual void removeFromScene(QGraphicsScene *scene);
	virtual void setVisible(bool visible) { m_item->setVisible(visible);}
	virtual void removeFromData(Data *data);
	protected:
	void setItem(QGraphicsPixmapItem *item) { m_item = item; }
	
};



#endif
