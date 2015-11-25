#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <QGraphicsItem>
class V_Node;
class Edge : public QGraphicsItem
{
public:
    Edge(V_Node *sourceNode, V_Node *destNode, QString infoOnEdge="");

    V_Node *sourceNode() const;
    V_Node *destNode() const;

    void adjust();
    void setEdgeColor(Qt::GlobalColor col){edgeColor = col;}
    void resetEdgeColor(){edgeColor = Qt::black;}

    enum { Type = UserType + 2 };
    int type() const { return Type; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    V_Node *source, *dest;

    qreal arrowSize;
    Qt::GlobalColor edgeColor;
    QPointF sourcePoint;
    QPointF destPoint;
    QString info;
};

#endif //GRAPH_EDGE_H
