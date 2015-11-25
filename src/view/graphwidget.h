#ifndef GRAPH_GRAPHWIDGET_H
#define GRAPH_GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

class V_Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    //GraphWidget(QWidget *parent = 0);
    GraphWidget(QWidget *parent=0,int sceneBoundX = 1900,int sceneBoundY = 1100,qreal scaleFactorX= 0.6,qreal scaleFactorY= 0.6);
    void itemMoved();
    virtual void populate();
    QList<V_Node *>& getListOfNode(){return listOfNode;}

public slots:
    virtual void shuffle();
    virtual void zoomIn();
    virtual void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    virtual void scaleView(qreal scaleFactor);

    QColor startBackgroundGradient;
    QColor endBackgroundGradient;
    QList<V_Node*> listOfNode;
    V_Node *centerNode=NULL;

private:
    int timerId;


};

#endif //GRAPH_GRAPHWIDGET_H
