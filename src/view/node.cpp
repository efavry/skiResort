#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

V_Node::V_Node(GraphWidget *graphWidget,int i,QString _text,bool isActive, bool isCenterNode)
    : graph(graphWidget),text(_text),id(i)
{
    if(isActive)
        setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    this->activated = isActive;
    this->centerNode = isCenterNode;
}

void V_Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> V_Node::edges() const
{
    return edgeList;
}

void V_Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this || centerNode || !activated)
    {
        newPos = pos();
        return;
    }

    // Sum up all forces pushing this item away
    //they come from the surrounding node
    qreal xvel = 0;
    qreal yvel = 0;
    qreal divideBy = 1.5; //default : 1 good one : 2
    foreach (V_Node *node, graph->getListOfNode())
    {
        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 1.0 * (dx * dx + dy * dy);
        if (l > 0)
        {
            xvel += (dx * 150.0)/(l /divideBy);
            yvel += (dy * 150.0)/ (l /divideBy);
        }
    }

    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1)*10; //increasing this value will result in farthest node
    foreach (Edge *edge, edgeList)
    {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    qreal stopThreshold = 4; //default : 1, nice one : 1.75
    if (qAbs(xvel) < stopThreshold && qAbs(yvel) < stopThreshold) //seuil d'arret
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    int burstingCoeff=20; //default : 100; other good one : 50; the smallest the farthest the node will go
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + burstingCoeff), sceneRect.right() - burstingCoeff));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + burstingCoeff), sceneRect.bottom() - burstingCoeff));
}

bool V_Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF V_Node::boundingRect() const
{

    qreal adjust = 100;
    return QRectF( -20 - adjust, -20 - adjust,
                  43 + adjust, 43 + adjust);
}

QPainterPath V_Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}



void V_Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken)
    {
        gradient.setCenter(1, 1);
        gradient.setFocalPoint(5, 5);
        gradient.setColorAt(1, QColor(40,40,40,128).light(120));
        gradient.setColorAt(0, QColor(0,0,0,64).light(120));
    }
    else
        //gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(0, QColor(255,255,255,128));
    if(elected==true)
        gradient.setColorAt(0, Qt::cyan);
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-20, -20, 40, 40);
    painter->drawText(QPointF(-(text.size()*3),4), text);
}

QVariant V_Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case ItemPositionHasChanged:
            foreach (Edge *edge, edgeList)
                edge->adjust();
            graph->itemMoved();
            break;
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void V_Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void V_Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
