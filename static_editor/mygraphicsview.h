#include <QGraphicsView>


class QWidget;
class QGraphicsScene;

class MyGraphicsView : public QGraphicsView {
public:
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);
	void mousePressEvent(QMouseEvent * event);
	
	
	
};
