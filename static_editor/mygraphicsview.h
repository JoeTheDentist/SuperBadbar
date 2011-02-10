#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QResizeEvent>

class MyGraphicsView : public QGraphicsView {
public:
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);
	void mousePressEvent(QMouseEvent * event);
	void resizeEvent ( QResizeEvent * event );
	
	
	
};
