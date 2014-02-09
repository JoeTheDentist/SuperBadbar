#include "SetItem.h"

#include <QGraphicsItem>
#include <iostream>
#include <QGraphicsScene>
#include <QInputDialog>

#include <util/paths.h>

SetItem::SetItem (QGraphicsScene *scene, QString fileName) :
    MyItem (NULL, fileName)
{
    QPixmap image;
    std::cout << SetItem::picPathFromEditor (fileName).toStdString() << std::endl;
    image.load (SetItem::picPathFromEditor (fileName) );
    setItem (scene->addPixmap (image) );
}

SetItem::~SetItem()
{

}

MyItem *SetItem::duplicate (QGraphicsScene *scene)
{
    SetItem *item = new SetItem (scene, m_file_name);
    item->getItem()->setVisible (false);
    return item;
}


void SetItem::saveItem (QTextStream &out)
{
    out << m_file_name << " " << m_item->x() << " " << m_item->y() << endl;
}

void SetItem::addToData (Data *data, bool push_front)
{
    data->addSetItem (this, push_front);
}


QString SetItem::picPathFromEditor (QString fileName)
{
    return SET_DIR + fileName + "_0.png";
}


