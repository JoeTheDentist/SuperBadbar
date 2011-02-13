#include "qcollisions_matrix.h"
#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include "mygraphicsview.h"

QCollisionsMatrix::QCollisionsMatrix(int width, int height)
{
	m_width = width;
	m_height = height;
	m_coll_item = new CollItem*[m_width];
	for (int i = 0; i < m_width; i++) {
		m_coll_item[i] = new CollItem[m_height];
		for (int j = 0; j < m_height; j++) {
			m_coll_item[i][j].item = NULL;
			m_coll_item[i][j].coll = NO_COLL;
		}
	}
}

QCollisionsMatrix::QCollisionsMatrix(QString fileName, MyGraphicsView *view)
{
	QFile file(fileName);
	file.open( QIODevice::ReadOnly | QIODevice::Text );
	QTextStream flux(&file);
	flux >> m_width;
	flux >> m_height;
	m_coll_item = new CollItem*[m_width];
	for (int i = 0; i < m_width; i++) {
		m_coll_item[i] = new CollItem[m_height];
		for (int j = 0; j < m_height; j++) {
			flux >> m_coll_item[i][j].coll;
			view->setBox(m_coll_item[i][j].coll, i * BOX_SIZE, j * BOX_SIZE);
		}
	}	

	file.close();
}

QCollisionsMatrix::~QCollisionsMatrix()
{
	for (int i = 0; i < m_width; i++) {
		delete[] m_coll_item[i];
	}
	delete[] m_coll_item;
}

int QCollisionsMatrix::width()
{
	return m_width;
}

int QCollisionsMatrix::height()
{
	return m_height;
}

int QCollisionsMatrix::coll(int i, int j)
{
	if (constraintError(i, j))
		return NO_COLL;
	return m_coll_item[i][j].coll;
}

QGraphicsItem *QCollisionsMatrix::item(int i, int j)
{
	if (constraintError(i, j))
		return NULL;
	return m_coll_item[i][j].item;
}

void QCollisionsMatrix::setColl(int coll, int i, int j)
{
	if (!constraintError(i, j))
		m_coll_item[i][j].coll = coll;
}

void QCollisionsMatrix::setItem(QGraphicsItem *item, int i, int j)
{
	if (!constraintError(i, j))
		m_coll_item[i][j].item = item;
}

bool QCollisionsMatrix::constraintError(int i, int j)
{
	return (i < 0 || i >= m_width || j < 0 || j >= m_height); 
}

void QCollisionsMatrix::save(QString fileName)
{
	QFile file(fileName);
	file.open( QIODevice::WriteOnly | QIODevice::Text );
	QTextStream out(&file);
	out << m_width << " " << m_height << endl;
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			out << m_coll_item[j][i].coll << " ";
		}
		out << endl;
	}
	file.close();
}
