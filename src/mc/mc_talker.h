#ifndef MC_TALKER_H
#define MC_TALKER_H
#include "mc_graph.h"
#include "mc_readdb.h"
#include "../view/graphwidget.h"
#include <list>
using namespace std;
class MC_talker
{
public:
    MC_talker();
    MC_talker(const MC_talker&);
    list<int> getNodeIDList();
    string getNodeNameFromId(int id);
    int getNodeAltitudeFromId(int id);
    list<int> getReachableNode(int id);
    void setGraphWidget(GraphWidget *graphWidget); //bouhahahah
private:
    GraphWidget *graphWidget;
    MC_graph *graph;
    MC_ReadDB *dbReader;
    MC_node* getNodeFromId(int id);
};

#endif // MC_TALKER_H
