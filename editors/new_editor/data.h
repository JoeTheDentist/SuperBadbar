#ifndef _EDITOR_DATA_H_
#define _EDITOR_DATA_H_

#include <list>
#include <QString>

class MyItem;

class Data {
	private:
	std::list<MyItem *> m_items;
	MyItem *m_background;
	int m_xpix;
	int m_ypix;
	
	public:
	Data();
	~Data();
	void setBackground(MyItem *item);
	void setLevelSize(int x, int y);
	void addItem(MyItem *item);
	void saveData(QString fileName);
	
};


#endif
