#include "StaticItem.h"

#include <QGraphicsItem>
#include <iostream>
#include <QGraphicsScene>
#include <QInputDialog>

#include <util/paths.h>

StaticItem::StaticItem (QGraphicsScene *scene, QString fileName, int buffer, unsigned int varCol) :
    MyItem (NULL, fileName),
    m_zbuffer (buffer),
    m_colVar (varCol)
{
    QPixmap image;
    image.load (StaticItem::picPathFromEditor (fileName) );
    setItem (scene->addPixmap (image) );
}

StaticItem::~StaticItem()
{

}

MyItem *StaticItem::duplicate (QGraphicsScene *scene)
{
    StaticItem *item = new StaticItem (scene, m_file_name, m_zbuffer, m_colVar);
    item->getItem()->setVisible (false);
    return item;
}


void StaticItem::saveItem (QTextStream &out)
{
    out << m_file_name << " " << m_item->x() << " " << m_item->y() << " " << m_zbuffer << " " << m_colVar << endl;
}

void StaticItem::addToData (Data *data, bool push_front)
{
    data->addStaticItem (this, push_front);
}

void StaticItem::edit()
{
    int entier = QInputDialog::getInteger (NULL, "ZBuffer", "Entrez le niveau de zbuffer (0 ou 1)");
    if (entier <= 0)
    {
        setStaticZBuffer (0);
    }
    else
    {
        setStaticZBuffer (1);
    }
}


QString StaticItem::picPathFromEditor (QString fileName)
{
    return STATIC_DIR + fileName + ".png";
}

void StaticItem::setStaticZBuffer (int buffer)
{
    m_zbuffer = buffer;
    if (m_zbuffer == 0)
    {
        this->getItem()->setZValue (STATICS_0_ZBUFFER);
    }
    else
    {
        this->getItem()->setZValue (STATICS_1_ZBUFFER);
    }
}
