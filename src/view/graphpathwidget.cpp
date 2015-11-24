#include "graphpathwidget.h"
#include "node.h"
#include "edge.h"

GraphPathWidget::GraphPathWidget()
    :GraphWidget::GraphWidget(0,1250,90,0.9,0.9)
{

    this->setMaximumSize(1250,90);
    startBackgroundGradient = QWidget::palette().color(QWidget::foregroundRole());
    endBackgroundGradient = startBackgroundGradient;

}



//inherited
void GraphPathWidget::populate()
{
    int nbNode=10;
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    centerNode = new Node(this,false);
    scene()->addItem(centerNode);
    centerNode->setPos(30, sceneBoundY/2);
    centerNode->setAsCenterNode();
    //QList<Node*> listOfNode;
    for(int i=0;i<nbNode;++i )
    {
        listOfNode.append(new Node(this,false));
    }
    Node *prevNode=centerNode;
    int i = 30;
    foreach(Node* n , listOfNode)
    {
        i+=(sceneBoundX/(nbNode+1));
        scene()->addItem(n);
        scene()->addItem(new Edge(prevNode,n));
        n->setPos(i,sceneBoundY /2);
        prevNode=n;
    }
}

void GraphPathWidget::shuffle(){return;}
void GraphPathWidget::zoomIn(){return;}
void GraphPathWidget::zoomOut(){return;}
void GraphPathWidget::scaleView(qreal scaleFactor)
{
    Q_UNUSED(scaleFactor);
    return;
}
