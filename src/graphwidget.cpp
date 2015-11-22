/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>
#include <math.h>

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
}


void GraphWidget::populate()
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    if(centerNode == NULL)
    {
        centerNode = new Node(this);
        scene()->addItem(centerNode);
        centerNode->setPos(sceneBoundX/2, sceneBoundY/2);
        centerNode->setAsCenterNode();
    }

    for(int i=0;i<36;++i )
    {
        listOfNode.append(new Node(this));
    }
    foreach(Node* n , listOfNode)
    {
        scene()->addItem(n);
        scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],n));
        for(int i=0;i<(qrand() % 2);++i )
        {
            scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],n));
        }
        n->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);

    }

    //now link randomly the center node
    scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],centerNode));
    for(int i=0;i<(qrand() % 2);++i )
    {
        scene()->addItem(new Edge(listOfNode[qrand() % listOfNode.size()],centerNode));
    }
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
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

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
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
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    int sceneBoundX=this->scene()->width();
    int sceneBoundY=this->scene()->height();
    foreach (QGraphicsItem *item, scene()->items())
    {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(qrand() % sceneBoundX,qrand() % sceneBoundY);
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
