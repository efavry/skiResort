#ifndef MC_TALKER_H
#define MC_TALKER_H
#include "mc_graph.h"
#include "mc_readdb.h"
#include "view/node.h"
#include "view/graphwidget.h"
#include <list>
#include <vector>
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

    //table de corespondance
    //node table
    vector<int> tableIdNode;
    vector<MC_node *> modelNode;
    vector<V_Node *> viewNode;

    //edge table
    vector<int> tableIdEdge;
    vector<MC_edge *> modelEdge;
    vector<Edge *> viewEdge;
};

#endif // MC_TALKER_H
