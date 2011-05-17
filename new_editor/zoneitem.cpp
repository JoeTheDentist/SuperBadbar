#include <QGraphicsPixmapItem>
#include <iostream>
#include "zoneitem.h"
#include "triggeritem.h"
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



ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, int x, int y):
	MyItem(NULL, ""),
	m_textEdit(NULL),
	m_parent(parent)
{

//~ 	setItem(scene->addRect(x, y, x + 10, y + 10));

	m_script += "#nature# monster	\n";
	m_script += "#text# \"fubob\"	\n";
	setPos(x, y);
}                

ZoneItem::ZoneItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser):
	MyItem(NULL, ""),
	m_textEdit(NULL),
	m_parent(parent)
{
	QPixmap image;
	image.load(ZoneItem::picPathFromEditor(""));
	setItem(scene->addPixmap(image));
	
	std::string keywork;
	std::string nature, text;
	int x = 0, y = 0;
	while (true) {
		keywork = analyser.read_between_char('#');
		if (keywork == "nature")
			m_script += QString::fromStdString("#nature# " + analyser.read_string() + "\n");
		else if (keywork == "x")
			x = analyser.read_int();
		else if (keywork == "y") 
			y = analyser.read_int();
		else if (keywork == "text") 
			m_script += QString::fromStdString("#text# " + analyser.read_string() + "\n");
		else if (keywork == "endtriggerable")
			break;
		else {
			break;
		}
	}	
	setPos(x, y);
}

ZoneItem::~ZoneItem()
{
	
}

MyItem *ZoneItem::duplicate(QGraphicsScene *scene)
{
//~ 	MyItem *item = new ZoneItem(scene, QString("../data/level/" + m_level_name + ".lvl"));
//~ 	item->getItem()->setVisible(false);
//~ 	return item;
	return NULL;
}

void ZoneItem::saveItem(QTextStream &out)
{
	out << "#x# " << x() << endl;
	out << "#y# " << y() << endl;
	out << m_script;
	out << "#endtriggerable# " << endl;
}

void ZoneItem::addToData(Data *data, bool push_front)
{
	std::cout << "add to data triggerable " << std::endl;
	m_parent->addZoneItem(this);
}

QString ZoneItem::picPathFromEditor(QString fileName)
{
	fileName = ""; //unused param
	return QString::fromStdString("../new_editor/images/triggerable.png");
}

void ZoneItem::edit()
{
	m_textEdit = new QTextEdit();
	m_textEdit->show();    
	m_textEdit->setPlainText(m_script);
	connect(m_textEdit, SIGNAL(textChanged()), this, SLOT(slotSetScriptText())); 
}


void ZoneItem::slotSetScriptText()
{
	m_script = m_textEdit->toPlainText();
}


