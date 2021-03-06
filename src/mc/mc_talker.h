#ifndef MC_TALKER_H
#define MC_TALKER_H
#include "mc_graph.h"
#include "mc_readdb.h"
#include "view/node.h"
#include "view/graphwidget.h"
#include <list>
#include <vector>
using namespace std;
class RightWidget;
class MC_talker
{
friend RightWidget;
public:
    MC_talker();
    void populate();
    list<int> getNodeIDList();
    string getNodeNameFromId(int id);
    int getNodeAltitudeFromId(int id);
    list<int> getReachableNode(int id);
    list<int> getReachableNodeWithCondition(int id,TypeRoute tr);
    void startShortestPath(int,int);
    void setGraphWidget(GraphWidget *graphWidget); //bouhahahah
private:
    MC_talker(const MC_talker&);
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

    MC_ReadDB db;

};

#endif // MC_TALKER_H
