#ifndef _MY_GRAPHICS_VIEW_
#define _MY_GRAPHICS_VIEW_
#include <QGraphicsView>


class QWidget;
class QGraphicsScene;
class QGraphicsItem;

class MyGraphicsView : public QGraphicsView {
	public:
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);
	void mousePressEvent(QMouseEvent * event);
	void loadFile(QString fileName);
	qreal xsize();
	qreal ysize();

	
	private:
	QGraphicsItem *m_background;
	qreal m_xsize;
	qreal m_ysize;
	
	
};

#endif
