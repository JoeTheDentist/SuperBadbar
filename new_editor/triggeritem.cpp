#include <QGraphicsPixmapItem>
#include <iostream>
#include "triggeritem.h"
#include "paths.h"
#include <QFile>
#include "analyser.h"
#include <QGraphicsScene>

#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>

TriggerItem::TriggerItem(QGraphicsScene *scene, QString fileName):
	MyItem(NULL, fileName),
	m_class_name(""),
	m_scene(scene)
{
	QPixmap image;
	image.load(TriggerItem::picPathFromEditor(fileName));
	setItem(scene->addPixmap(image));
	m_class_name = "event";
}                


TriggerItem::~TriggerItem()
{
	
}

MyItem *TriggerItem::duplicate(QGraphicsScene *scene)
{
	MyItem *item = new TriggerItem(scene, m_file_name);
	item->getItem()->setVisible(false);
	return item;
}

void TriggerItem::saveItem(QTextStream &out)
{
	out << m_class_name << " " << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
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
	QGroupBox *groupbox = new QGroupBox("Votre plat préféré", NULL);

    QRadioButton *steacks = new QRadioButton("Les steacks");
    QRadioButton *hamburgers = new QRadioButton("Les hamburgers");
    QRadioButton *nuggets = new QRadioButton("Les nuggets");

    steacks->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(steacks);
    vbox->addWidget(hamburgers);
    vbox->addWidget(nuggets);

    groupbox->setLayout(vbox);
    groupbox->move(5, 5);

}
