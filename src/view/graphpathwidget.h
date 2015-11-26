#ifndef GRAPH_GRAPHPATHWIDGET_H
#define GRAPH_GRAPHPATHWIDGET_H
#include "graphwidget.h"
#include "mc_type.h"

class GraphPathWidget : public GraphWidget
{
public:
    GraphPathWidget();
    //void populate();
public slots:
    virtual void shuffle();
    virtual void zoomIn();
    virtual void zoomOut();


private :
    void scaleView(qreal scaleFactor);
};

#endif // GRAPHPATHWIDGET_H
