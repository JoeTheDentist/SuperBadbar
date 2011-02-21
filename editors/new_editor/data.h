#ifndef _EDITOR_DATA_H_
#define _EDITOR_DATA_H_

#include <list>
#include <QString>

class QGraphicsItem;
class MyItem;

class Data {
	private:
	std::list<MyItem *> m_static_items;
	QString m_background_name;
	QGraphicsItem *m_background;
	int m_xpix;
	int m_ypix;
	
	public:
	Data();
	~Data();
	void setBackground(QGraphicsItem *item, QString fileName);
	void setLevelSize(int x, int y);
	void addItem(MyItem *item);
	void addStaticItem(MyItem *item);
	void saveData(QString fileName);
	
};


#endif
