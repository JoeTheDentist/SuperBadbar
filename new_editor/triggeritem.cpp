#include <QGraphicsItem>
#include <iostream>
#include <sstream>
#include "triggeritem.h"
#include "triggerableitem.h"
#include "zoneitem.h"
#include "mygraphicsview.h"
#include "utils.h"
#include <QFile>
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QWidget>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>
#include <QMenu>
#include <QAction>


TriggerItem::TriggerItem(QGraphicsScene *scene, QString fileName, Analyser *analyser):
	MyItem(NULL, fileName),
	m_class_name(""),
	m_level_name(fileName),
	m_scene(scene),
	m_textEdit(NULL)
{
	if (analyser == NULL) {
		createTrigger(scene, fileName);
	} else {
		loadTrigger(scene, fileName, analyser);
	}
}                

void TriggerItem::createTrigger(QGraphicsScene *scene, QString fileName) 
{
	m_level_name =  substringAfter(fileName, "levels/");
	m_level_name = suppressExtension(m_level_name); // on enleve .lvl
	QPixmap image;
	image.load(TriggerItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	m_class_name = "event";
	m_script += "#zone#				\n";
	m_script += "1					\n";
	m_script += "0 0 100 5000		\n";
	m_script += "\n";
	setPos(0, 0);	
}

void TriggerItem::loadTrigger(QGraphicsScene *scene, QString fileName, Analyser *analyser)
{
	m_level_name =  substringAfter(fileName, "levels/");
	m_level_name = suppressExtension(m_level_name); // on enleve .lvl
	QPixmap image;
	image.load(TriggerItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	analyser->find_next_string("#editor pos#");
	int x = analyser->read_int();
	int y = analyser->read_int();
	std::cout << x << " " << y << std::endl;
	setPos(x, y);	
	//chargement des zoneitem
	analyser->find_next_string("#zone#");
	int nbZones = analyser->read_int();
	for (int i = 0; i < nbZones; i++) {
		ZoneItem *newItem = new ZoneItem(m_scene, this, *analyser);
		newItem->addToData(m_view->getData());
	}
	// chargement des triggerablesitem
	analyser->find_next_string("#triggerables#");
	int nbTriggers = analyser->read_int();
	for (int i = 0; i < nbTriggers; i++) {
		TriggerableItem *newItem = new TriggerableItem(m_scene, this, *analyser);
		newItem->addToData(m_view->getData());
	}
	m_class_name = "event";
	

}

TriggerItem::~TriggerItem()
{
}

MyItem* TriggerItem::selectItem(int x, int y)
{
	MyItem *res = MyItem::selectItem(x, y);
	if (res)
		return res;
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		res = (*it)->selectItem(x, y);
		if (res)
			return res;
	}
	for (std::list<ZoneItem *>::iterator it = m_zones.begin();
			it != m_zones.end(); it++) {
		res = (*it)->selectItem(x, y);
		if (res)
			return res;
	}
	return NULL;
}


MyItem *TriggerItem::duplicate(QGraphicsScene *scene)
{
	MyItem *item = new TriggerItem(scene, QString("../data/level/" + m_level_name + ".lvl"));
	item->getItem()->setVisible(false);
	return item;
}

void TriggerItem::saveItem(QTextStream &out)
{
	out << "#trig#" << endl;
	out << "#editor pos#" << endl;
	out << x() << " " << y() << endl;
	out << "#zone#" << endl;
	out << m_zones.size() << endl;
	for (std::list<ZoneItem *>::iterator it = m_zones.begin();
			it != m_zones.end(); it++) {
		(*it)->saveItem(out);
	}
	out << "#triggerables#" << endl;
	out << m_triggerables.size() << endl;
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		(*it)->saveItem(out);
	}
	out << endl;
}

void TriggerItem::addToData(Data *data, bool push_front)
{
	data->addTriggerItem(this, push_front);
}

QString TriggerItem::picPathFromEditor(QString fileName)
{
	fileName = ""; //unused param
	return QString::fromStdString("../new_editor/images/trigger.png");
}

void TriggerItem::edit()
{
	m_textEdit = new QTextEdit();
	m_textEdit->show();    
	m_textEdit->setPlainText(m_script);
	connect(m_textEdit, SIGNAL(textChanged()), this, SLOT(slotSetScriptText())); 

}

void TriggerItem::setPos(int x, int y)
{
	MyItem::setPos(x, y);
	updateLines();
}


void TriggerItem::slotSetScriptText()
{
	m_script = m_textEdit->toPlainText();
}

void TriggerItem::addTriggerableItem(TriggerableItem *item)
{
	m_triggerables.push_front(item);
}

void TriggerItem::addZoneItem(ZoneItem *item)
{
	m_zones.push_front(item);
}

void TriggerItem::rightClic(int x, int y)
{
	QPoint pos(x, y);
	QMenu *menu = new QMenu(NULL);
	QAction *actionAddPos = new QAction("Add position", NULL);
	connect(actionAddPos, SIGNAL(triggered()), this, SLOT(slotAddPosition()));	
	QAction *actionAddTriggerable = new QAction("Add triggerable", NULL);
	connect(actionAddTriggerable, SIGNAL(triggered()), this, SLOT(slotAddTriggerable()));	
	menu->addAction(actionAddPos);
	menu->addAction(actionAddTriggerable);
	menu->move(m_view->getWindow()->mapToGlobal(pos));
	menu->show();
}

void TriggerItem::slotAddPosition()
{
	std::cout << "Add POsition" << std::endl;
	ZoneItem *newItem = new ZoneItem(m_scene, this);
	m_view->setStateAddingItem(newItem);
}

void TriggerItem::slotAddTriggerable()
{	
	std::cout << "Add triggerable" << std::endl;
	TriggerableItem *newItem = new TriggerableItem(m_scene, this);
	m_view->setStateAddingItem(newItem);
}

void TriggerItem::removeFromScene(QGraphicsScene *scene)
{
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		(*it)->removeFromScene(scene);
	}
	for (std::list<ZoneItem *>::iterator it = m_zones.begin();
			it != m_zones.end(); it++) {
		(*it)->removeFromScene(scene);
	}
	MyItem::removeFromScene(scene);
}

bool TriggerItem::removeItem(MyItem *item)
{
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		if((*it) == item) {
			std::cout << "erasing triggerable" << std::endl;
			m_triggerables.erase(it);
			return true;
		}
	}
	for (std::list<ZoneItem *>::iterator it = m_zones.begin();
			it != m_zones.end(); it++) {
		if((*it) == item) {
			std::cout << "erasing zone" << std::endl;
			m_zones.erase(it);
			return true;
		}
	}
	
	return false;
}

void TriggerItem::updateLines()
{
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		(*it)->updateLine();
	}
	for (std::list<ZoneItem *>::iterator it = m_zones.begin();
			it != m_zones.end(); it++) {
				
	}
}


