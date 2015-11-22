#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

Node::Node(GraphWidget *graphWidget,bool isActive)
    : graph(graphWidget)
{
    if(isActive)
        setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    this->activated = isActive;
    this->centerNode = false;
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this || centerNode || !activated)
    {
        newPos = pos();
        return;
    }

    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    qreal divideBy = 1.5; //default : 1 good one : 2
    foreach (QGraphicsItem *item, scene()->items())
    {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 1.0 * (dx * dx + dy * dy);
        //std::cout << "lol" << l << std::endl;

        if (l > 0)
        {
            xvel += (dx * 150.0)/(l /divideBy);
            yvel += (dy * 150.0)/ (l /divideBy);
        }
    }

    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1) * 10;
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
    int burstingCoeff=100; //default : 100; other good one : 50; the smallest the farthest the node will go
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + burstingCoeff), sceneRect.right() - burstingCoeff));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + burstingCoeff), sceneRect.bottom() - burstingCoeff));
}

bool Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF Node::boundingRect() const
{

    qreal adjust = 100;
    return QRectF( -20 - adjust, -20 - adjust,
                  43 + adjust, 43 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}



void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    //painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkGray);
    //painter->drawEllipse(-7, -7, 20, 20);
    //this->shape()
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
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-20, -20, 40, 40);


    if(centerNode)
    {
        painter->drawText(QPointF(-30,4), QString("CenterNode"));
    }
    else
    {
        QString txtToPrint("t");
        txtToPrint.append(QString::number(this->pos().x()));
        std::cout << txtToPrint.toStdString() << std::endl;
        std::cout << txtToPrint.size() << std::endl;
        painter->drawText(QPointF(-(txtToPrint.size()*3),4), txtToPrint);
    }
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
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

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
