//TODO : info on edge, draw an arc for the edge

#include <QPainter>
#include "edge.h"
#include "node.h"

#include <math.h>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(V_Node *sourceNode, V_Node *destNode,int id,QString _name,int _distance,int _temps, TypeRoute _typeRoute)
    : arrowSize(10),idEdge(id),name(_name),distance(_distance),temps(_temps),typeRoute(_typeRoute)
{
    setAcceptedMouseButtons(0);
    edgeColor=findEdgeColor(_typeRoute);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    offset = qrand()%5;
    adjust();
}

V_Node *Edge::sourceNode() const
{
    return source;
}

V_Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    }
    else
    {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    //qreal penWidth = 1;
    //qreal extra = (penWidth + arrowSize) / 2.0;
    qreal extra =400;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
                                                                       .normalized()
                                                                                    .adjusted(-extra, -extra, extra, extra);
    //return QRect(sourcePoint, QSizeF )
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line((sourcePoint.x())+this->offset,
                (sourcePoint.y())+this->offset,
                (destPoint.x())+this->offset,
                (destPoint.y())+this->offset);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(this->edgeColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

/*    QPainterPath path;
    path.moveTo(sourcePoint);//c0
    //c1 puis c2 puis c3
    path.cubicTo(sourcePoint.x()+ line.dx()/3,sourcePoint.y(), //c1
                 destPoint.x()- line.dx()/3,destPoint.y(), //c2
                 destPoint.x(),destPoint.y()); //endpoint
    painter->drawPath(path);
*/
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);
    painter->setBrush(Qt::darkBlue);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

    //draw info text
    painter->setPen(QPen(Qt::black, 0));
    //std::cout << this->info.size() << std::endl;
    QString info(name);
    painter->drawText(sourcePoint.x() + line.dx()/2,sourcePoint.y()+(line.dy()/2)/*,Qt::AlignHCenter,*/,info);
    info.clear();
    info.append("Distance : ");
    info.append(QString::number(distance));
    painter->drawText(sourcePoint.x() + line.dx()/2,sourcePoint.y()+(line.dy()/2)+10/*,Qt::AlignHCenter,*/,info);
    info.clear();
    info.append("Temps : ");
    info.append(QString::number(temps));
    painter->drawText(sourcePoint.x() + line.dx()/2,sourcePoint.y()+(line.dy()/2)+20/*,Qt::AlignHCenter,*/,info);
}

QColor Edge::findEdgeColor(TypeRoute typeR)
{
    switch (typeR)
    {
        case TypeRoute::V:
            return Qt::green;
        case TypeRoute::B:
            return Qt::blue;
        case TypeRoute::R:
            return Qt::red;
        case TypeRoute::N:
            return Qt::black;
        default:
            return Qt::gray;
    }
}
