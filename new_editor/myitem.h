#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

class Data;
class QGraphicsItem;
class MyGraphicsView;

enum miState {
	e_beingAdded, e_beingMoved, e_selected, e_beingResized, e_nothing
};

class MyItem {
	protected:
	static MyGraphicsView *m_view;
	QGraphicsItem *m_item;
	miState m_state;
	QString m_file_name;
	
	
	public:
	MyItem(QGraphicsItem *item, QString fileName, miState state = e_beingAdded);
	virtual ~MyItem();
	static void setView(MyGraphicsView *view);
	static MyGraphicsView *getView();
	virtual MyItem *duplicate(QGraphicsScene *scene) = 0;
	QGraphicsItem *getItem();
	virtual int x() {return m_item->x();}
	virtual int y() {return m_item->y();}
	virtual void saveItem(QTextStream &out) = 0;
	virtual void addToData(Data *data, bool push_front = true) = 0;
	virtual void signalEndOfAdding();
	virtual void edit();
	virtual void mouseMoved(int x, int y);
	virtual void rightClic(int x, int y) { x = 0; y = 0; std::cout << "right clic" << std::endl; }
	virtual void moveItem(int xrel, int yrel, int xabs = 0, int yabs = 0);
	virtual void setPos(int x, int y);
	virtual MyItem* selectItem(int x, int y);
	virtual void removeFromScene(QGraphicsScene *scene);
	virtual void setVisible(bool visible) { m_item->setVisible(visible);}
	virtual void removeFromData(Data *data);
	virtual void setStateBeingAdded() {m_state = e_beingAdded;}
	virtual void setStateBeingMoved() {m_state = e_beingMoved;}
	virtual void setStateSelected(); 
	virtual void setStateNothing();
	bool isBeingAdded() const {return m_state == e_beingAdded ;}
	bool isBeingMoved() const {return m_state == e_beingMoved ;}
	bool isSelected() const {return m_state == e_selected ;}
	bool isNothing() const {return m_state == e_nothing ;}
	protected:
	void setItem(QGraphicsItem *item) { m_item = item; }
	
};



#endif
