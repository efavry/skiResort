#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;
class MC_talker;
class V_Node : public QGraphicsItem
{
friend GraphWidget;
friend MC_talker;
public:
    V_Node(GraphWidget *graphWidget,int i=-1,QString _text=QString(),int _altitude=0, bool isActive = true, bool isCenterNode = false);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool isCenterNode(){return centerNode;}
    void setAsCenterNode(){centerNode=true;}

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    int id;
    QString text="";
    int altitude;
    bool elected=false;
    bool activated;
    bool centerNode;
};

#endif // GRAPH_NODE_H
