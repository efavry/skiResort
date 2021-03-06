#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>
#include <math.h>
//#include <QGLWidget>

GraphWidget::GraphWidget(QWidget *parent,
                         int sceneBoundX,
                         int sceneBoundY,
                         qreal scaleFactorX,
                         qreal scaleFactorY)
    : QGraphicsView(parent), timerId(0)
{
    this->setStyleSheet("background:transparent;");
    startBackgroundGradient = Qt::white;
    endBackgroundGradient = Qt::lightGray;
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,sceneBoundX,sceneBoundY);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(scaleFactorX, scaleFactorY);
    //setViewport(new QGLWidget());
}
/*
void GraphWidget::addNode(V_Node *vn)
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    listOfNode.append(vn);
    scene()->addItem(vn);
    vn->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
}

void GraphWidget::addCenterNode(V_Node *vn)
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    listOfNode.append(vn);
    scene()->addItem(vn);
    vn->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
    centerNode = vn;
}
*/
/*
void GraphWidget::connectNode(V_Node*from,V_Node*to)
{
    scene()->addItem(new Edge(from,to));
}
*/
/*
void GraphWidget::populate()
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    if(centerNode == NULL)
    {
        centerNode = new V_Node(this,1,QString("lol"),true,true);
        scene()->addItem(centerNode);
        centerNode->setPos(sceneBoundX/2, sceneBoundY/2);
        listOfNode.append(centerNode);
        //centerNode->setAsCenterNode();
    }
    QList<V_Node *> listOfNodeToAdd;
    for(int i=0;i<36;++i )
    {
        listOfNodeToAdd.append(new V_Node(this,1,QString()));
    }
    foreach(V_Node* n , listOfNodeToAdd)
    {
        scene()->addItem(n);
        scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],n));
        for(int i=0;i<(qrand() % 2);++i )
        {
            scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],n,QString("to witness the beauty of the ").append(QString::number(i)).append(" run")));
        }
        listOfNode.append(n);
        n->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);

    }

    //now link randomly the center node
    scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],centerNode,QString("I Wish I was there")));
    for(int i=0;i<(qrand() % 2);++i )
    {
        scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],centerNode,QString("to witness the beauty of the ").append(QString::number(i)).append(" run") ));
    }
}
*/

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            centerNode->moveBy(0, -20);
            break;
        case Qt::Key_Down:
            centerNode->moveBy(0, 20);
            break;
        case Qt::Key_Left:
            centerNode->moveBy(-20, 0);
            break;
        case Qt::Key_Right:
            centerNode->moveBy(20, 0);
            break;
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Space:
        case Qt::Key_Enter:
            shuffle();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
/*
    QList<V_Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items())
    {
        if (V_Node *node = qgraphicsitem_cast<V_Node *>(item))
            nodes << node;
    }
*/
    foreach (V_Node *node, listOfNode)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (V_Node *node, listOfNode)
    {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved)
    {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, startBackgroundGradient);
    gradient.setColorAt(1, endBackgroundGradient);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    //painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

//signals
void GraphWidget::shuffle()
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    /*foreach (QGraphicsItem *item, scene()->items())
    {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
    }*/

    foreach (V_Node *n , listOfNode)
    {
            n->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::electSignal(int i)
{

    foreach (V_Node* vn, this->listOfNode)
        if(vn->id == i)
        {
            vn->elected = true;
            vn->update();
        }
}
void GraphWidget::resetElection()
{
    foreach (V_Node* vn, this->listOfNode)
     {
        vn->elected = false;
        vn->update();
    }
}

void GraphWidget::createNode(int id,string name,int altitude)
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    V_Node* vn;
    if(centerNode!=NULL)
        vn= new V_Node(this,id,QString::fromStdString(name),altitude);
    else
    {
        vn = new V_Node(this,id,QString::fromStdString(name),altitude,true,true);
        centerNode =vn;
    }
    listOfNode.append(vn);
    scene()->addItem(vn);
    vn->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
}
void GraphWidget::createEdge(int fromId,int destId,int id,string name,int distance,int temps,TypeRoute typeRoute)
{
    //first we retrieve the source node
    V_Node* vnSource=NULL;
    V_Node* vnDest=NULL;
    foreach(V_Node* vnSourceIt,listOfNode)
        if(vnSourceIt->id == fromId)
        {
            vnSource=vnSourceIt;
            break; //BEEEEEEH
        }
    //then retrieve the dest node
    foreach(V_Node* vnDestIt,listOfNode)
        if(vnDestIt->id == destId)
        {
            vnDest=vnDestIt;
            break; //BEEEEEEH
        }
    //then we create the edge
    if(vnSource!=NULL && vnDest!=NULL)
    {
        Edge *edgeToAdd = new Edge(vnSource,vnDest,id,QString::fromStdString(name),distance,temps,typeRoute);
        listOfEdge.append(edgeToAdd);
        scene()->addItem(edgeToAdd);
    }
}
