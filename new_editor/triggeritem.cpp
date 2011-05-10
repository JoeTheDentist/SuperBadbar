#include <QGraphicsPixmapItem>
#include <iostream>
#include "triggeritem.h"
#include "mygraphicsview.h"
#include "utils.h"
#include <QFile>
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>

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
	m_level_name =  m_level_name.right(m_level_name.size() - (m_level_name.lastIndexOf("levels/") + 7));
	m_level_name = suppressExtension(m_level_name); // on enleve .lvl
	std::cout << "FILE NAME : " << m_level_name.toStdString() << std::endl;
	m_trigger_id = id;
	id++;
	QPixmap image;
	image.load(TriggerItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	m_class_name = "event";
	m_script += "#zone#				\n";
	m_script += "1					\n";
	m_script += "0 0 100 5000		\n";
	m_script += "\n";
	m_script += "#triggerables#		\n";
	m_script += "1					\n";
	m_script += "#nature# monster	\n";
	m_script += "#x# 130			\n";
	m_script += "#y# 3100			\n";
	m_script += "#text# \"fubob\"	\n";
	m_script += "#endtriggerable#	\n";
	setPos(x, y);
}                


TriggerItem::~TriggerItem()
{
	
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
	outtrig << m_script;
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
	std::cerr << "edit de triggeritem" << std::endl ;
//~ 	
	m_textEdit = new QTextEdit();
	m_textEdit->show();    
	m_textEdit->setPlainText(m_script);
	connect(m_textEdit, SIGNAL(textChanged()), this, SLOT(setScriptText())); 
	

//~ 	
//~ 	QGroupBox *groupbox = new QGroupBox("Votre plat préféré", getView()->getWindow());

//~     QRadioButton *steacks = new QRadioButton("Les steacks");
//~     QRadioButton *hamburgers = new QRadioButton("Les hamburgers");
//~     QRadioButton *nuggets = new QRadioButton("Les nuggets");

//~     steacks->setChecked(true);

//~     QVBoxLayout *vbox = new QVBoxLayout;
//~     vbox->addWidget(steacks);
//~     vbox->addWidget(hamburgers);
//~     vbox->addWidget(nuggets);

//~     groupbox->setLayout(vbox);
//~     groupbox->move(5, 5);

}

void TriggerItem::setScriptText()
{
	m_script = m_textEdit->toPlainText();
}
