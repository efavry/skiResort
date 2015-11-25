#include "list"
#include "mc_talker.h"
#include <QString>
using namespace std;
MC_talker::MC_talker()
{
    graph = new MC_graph();
    /*for (int i=0; i<35 ; ++i)
    {
        graph->addNode(new MC_node(i,QString::number(i).append("test").toStdString(),10000));
        graph->connectNode(graph->listOfNodes[]);
    }*/
    MC_node *node1=new MC_node(0,QString("ipsum node").toStdString(),10000);
    MC_node *node2=new MC_node(1,QString("quia node").toStdString(),10000);
    MC_node *node3=new MC_node(2,QString("dolor node").toStdString(),10000);
    MC_node *node4=new MC_node(3,QString("sit node").toStdString(),10000);
    MC_node *node5=new MC_node(4,QString("amet node").toStdString(),10000);
    MC_node *node6=new MC_node(5,QString("gauss node").toStdString(),10000);

    graph->addNode(node1);
    graph->addNode(node2);
    graph->addNode(node3);
    graph->addNode(node4);
    graph->addNode(node5);
    graph->addNode(node6);

    graph->connectNode(node1,node2);
    graph->connectNode(node2,node3);
    graph->connectNode(node3,node4);
    graph->connectNode(node4,node5);

}

list<int> MC_talker::getNodeIDList()
{
    list<int> idList;
    for(MC_node* n: graph->getListOfNodes())
            idList.push_back(n->id);
    return idList;
}
string MC_talker::getNodeNameFromId(int id)
{
    for(MC_node* n: graph->getListOfNodes())
            if (n->id == id)
                return n->name;
}
int MC_talker::getNodeAltitudeFromId(int id)
{
    for(MC_node* n: graph->getListOfNodes())
            if (n->id == id)
                return n->altitude;
    return -1;
}

MC_node* MC_talker::getNodeFromId(int id)
{
    for(MC_node* n: graph->getListOfNodes())
        if(n->id == id)
            return n;
    return NULL;
}

list<int> MC_talker::getReachableNode(int id)
{
    list<MC_node *> listOfReachedNode;
    listOfReachedNode = graph->dfs(getNodeFromId(id));

    list<int> listOfNodeId;
    for(MC_node *n:listOfReachedNode)
        listOfNodeId.push_back(n->id);
    return listOfNodeId;
}

void MC_talker::setGraphWidget(GraphWidget *graph)
{
    graphWidget=graph;
    graph->
}
