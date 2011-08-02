#include "TriggerableItem.h"

#include <QGraphicsItem>
#include <iostream>
#include <QFile>
#include <QGraphicsScene>
#include <QWidget>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QGraphicsLineItem>
#include <QPen>

#include <editor/MainWindow.h>
#include <items/TriggerItem.h>
#include <editor/MyGraphicsView.h>
#include <util/utils.h>

TriggerableItem::TriggerableItem(QGraphicsScene *scene, TriggerItem *parent, int x, int y):
	MyItem(NULL, ""),
	m_textEdit(NULL),
	m_parent(parent), 
	m_itemSegment(NULL)
{
	// chargement du qgraphicsitem
	QPixmap image;
	image.load(TriggerableItem::picPathFromEditor(""));
	setItem(scene->addPixmap(image));

	// valeur par defaut du m_script
	m_script += "#nature# monster	\n";
	m_script += "#text# \"fubob\"	\n";
	
	// maj de la position
	setPos(x, y);
}                

TriggerableItem::TriggerableItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser):
	MyItem(NULL, ""),
	m_textEdit(NULL),
	m_parent(parent), 
	m_itemSegment(NULL)
{
	// chargement du qgraphicsitem
	QPixmap image;
	image.load(TriggerableItem::picPathFromEditor(""));
	setItem(scene->addPixmap(image));
	
	// chargement du m_script
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
			m_script += QString::fromStdString("#text# \"" + analyser.read_between_char('"') + "\""+ "\n");
		else if (keywork == "endtriggerable")
			break;
		else {
			break;
		}
	}	
	
	// maj de la position
	setPos(x, y);
	addLine();
}

TriggerableItem::TriggerableItem(TriggerableItem &original):
	QObject(),
	MyItem(NULL, "", e_beingAdded),
	m_script(original.m_script),
	m_textEdit(NULL),
	m_parent(original.m_parent)	, 
	m_itemSegment(NULL)
{
	// chargement du qgraphicsitem
	QPixmap image;
	image.load(TriggerableItem::picPathFromEditor(""));
	setItem(m_view->scene()->addPixmap(image));	
	addLine();
}

TriggerableItem::~TriggerableItem()
{
	
}

MyItem *TriggerableItem::duplicate(QGraphicsScene *scene)
{
	Q_UNUSED(scene);
	MyItem *newitem = new TriggerableItem(*this);
	newitem->getItem()->setVisible(false);
	addLine();
	return newitem;
}

void TriggerableItem::saveItem(QTextStream &out)
{
	out << "#x# " << x() << endl;
	out << "#y# " << y() << endl;
	out << m_script;
	out << "#endtriggerable# " << endl;
}

void TriggerableItem::addToData(Data *data, bool push_front)
{
	Q_UNUSED(data); Q_UNUSED(push_front);
	m_parent->addTriggerableItem(this);
}

QString TriggerableItem::picPathFromEditor(QString fileName)
{
	fileName = ""; //unused param
	return QString::fromStdString("../new_editor/images/triggerable.png");
}

void TriggerableItem::edit()
{
	m_textEdit = new QTextEdit();
	m_textEdit->show();    
	m_textEdit->setPlainText(m_script);
	connect(m_textEdit, SIGNAL(textChanged()), this, SLOT(slotSetScriptText())); 
}

void TriggerableItem::removeFromScene(QGraphicsScene *scene)
{
	scene->removeItem(m_itemSegment);
	MyItem::removeFromScene(scene);
}


void TriggerableItem::slotSetScriptText()
{
	m_script = m_textEdit->toPlainText();
}

void TriggerableItem::setPos(int x, int y)
{
	MyItem::setPos(x, y);
	std::cout << "plop" << std::endl;
	updateLine();
}

void TriggerableItem::updateLine()
{
	if (m_parent && m_itemSegment)
		m_itemSegment->setLine(x(), y(), m_parent->x(), m_parent->y());
	std::cout << m_parent->x() << m_parent->y() << std::endl;
}

void TriggerableItem::addLine()
{
	m_itemSegment = new QGraphicsLineItem(0, 0, 0, 0);
	QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	m_itemSegment->setPen(pen);
	getView()->scene()->addItem(m_itemSegment);
	updateLine();
}

