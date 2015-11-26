#ifndef GRAPH_GRAPHWIDGET_H
#define GRAPH_GRAPHWIDGET_H
#include "mc_type.h"
#include <QtGui/QGraphicsView>
#include <string>
using namespace std;
class Edge;
class V_Node;
class MC_talker;
class GraphWidget : public QGraphicsView
{

    Q_OBJECT
friend MC_talker;
public:
    //GraphWidget(QWidget *parent = 0);
    GraphWidget(QWidget *parent=0,int sceneBoundX = 1900,int sceneBoundY = 1000,qreal scaleFactorX= 0.6,qreal scaleFactorY= 0.6);
    void itemMoved();
    //virtual void populate();
    QList<V_Node *>& getListOfNode(){return listOfNode;} //attention a pas faire l'idiot avec ça
    //void addNode(V_Node*);
    //void addCenterNode(V_Node*);
    void connectNode(V_Node*,V_Node*);


public slots:
    virtual void shuffle();
    virtual void zoomIn();
    virtual void zoomOut();
    void createNode(int id,string name,int altitude);
    void createEdge(int fromId,int destId,int id,string name,int distance,int temps,TypeRoute typeRoute);

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    virtual void scaleView(qreal scaleFactor);

    QColor startBackgroundGradient;
    QColor endBackgroundGradient;
    QList<Edge*> listOfEdge;
    QList<V_Node*> listOfNode;
    V_Node *centerNode=NULL;

private:
    int timerId;


};

#endif //GRAPH_GRAPHWIDGET_H
