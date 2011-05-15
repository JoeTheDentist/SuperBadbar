#include <QGraphicsPixmapItem>
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


TriggerItem::TriggerItem(QGraphicsScene *scene, QString fileName, int trigind, int x, int y):
	MyItem(NULL, fileName),
	m_trigger_id(0),
	m_class_name(""),
	m_level_name(fileName),
	m_scene(scene),
	m_textEdit(NULL)
{
	static int id = 0;
	if (trigind != -1) {
		id = trigind;
	}
	m_trigger_id = id;
	id++;
	if (trigind == -1) {
		createTrigger(scene, fileName);
	} else {
		loadTrigger(scene, fileName, trigind, x, y);
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

void TriggerItem::loadTrigger(QGraphicsScene *scene, QString fileName, int trigind, int x, int y)
{
	std::cout << "Chargement de trigger item " << std::endl;
	m_level_name =  substringAfter(fileName, "levels/");
	m_level_name = suppressExtension(m_level_name); // on enleve .lvl
	QString trigdir = LEVELS_DIR + m_level_name + "triggers/";
	std::cout << "trigdir: " << trigdir.toStdString() << std::endl;
	QPixmap image;
	image.load(TriggerItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	// chargement des triggerablesitem
	std::stringstream triggerFileName;
	triggerFileName << trigdir.toStdString() << "trig" << trigind << ".trg";
	Analyser analyser;
	analyser.open(triggerFileName.str());
	analyser.find_string("#triggerables#");
	int nbTriggers = analyser.read_int();
	for (int i = 0; i < nbTriggers; i++) {
		TriggerableItem *newItem = new TriggerableItem(m_scene, this, analyser);
		newItem->addToData(m_view->getData());
	}
	m_class_name = "event";
	m_script += "#zone#				\n";
	m_script += "1					\n";
	m_script += "0 0 100 5000		\n";
	m_script += "\n";
	analyser.close();
	setPos(x, y);	
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
	//creatin du .trg
	QString reldir = m_level_name + "triggers/";
	QString dir = QString(LEVELS_DIR) + reldir;
	std::cout << "Dir : " << dir.toStdString() << std::endl;
	if (!QDir(dir).exists()) {
		std::cout << "Creation du repertoire " << dir.toStdString() << std::endl;
		QDir().mkdir(dir);	
	}
	QString trigfile;
	QTextStream trigstream(&trigfile);
	trigstream << dir << "trig" << m_trigger_id << ".trg";
	QFile file(trigfile);
	file.open( QIODevice::WriteOnly | QIODevice::Text );
	QTextStream outtrig(&file);
	//ecriture dans le .trg
	outtrig << m_script;
	outtrig << "#triggerables#" << endl;
	outtrig << m_triggerables.size() << endl;
	for (std::list<TriggerableItem *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); it++) {
		(*it)->saveItem(outtrig);
	}
	
	file.close();
	
	//save dans le .lvl
	out << m_trigger_id << " " << x() << " " << y() << endl;

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
	return false;
}
