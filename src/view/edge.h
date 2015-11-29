#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H
#include "mc_type.h"
#include <iostream>
#include <QGraphicsItem>
class GraphWidget;
class V_Node;
class Edge : public QGraphicsItem
{
friend GraphWidget;
public:
    Edge(V_Node *sourceNode, V_Node *destNode,int id,QString _name=QString(),int distance=0,int temps=0,TypeRoute typeRoute = TypeRoute::NONE);
    V_Node *sourceNode() const;
    V_Node *destNode() const;

    void adjust();
    void setEdgeColor(QColor col){edgeColor = col;}
    void resetEdgeColor(){edgeColor = Qt::black;}

    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QColor findEdgeColor(TypeRoute typeR);
    V_Node *source, *dest;

    qreal arrowSize;
    QColor edgeColor;
    QPointF sourcePoint;
    QPointF destPoint;
    int idEdge;
    QString name;
    int distance;
    int temps;
    TypeRoute typeRoute;
    int offset;

    bool showName=false;
    bool showTime=false;
    bool showDistance=false;
};

#endif //GRAPH_EDGE_H
