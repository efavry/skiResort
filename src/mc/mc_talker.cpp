#include "list"
#include "mc_talker.h"
#include "../view/node.h"
#include <iostream>
#include <list>
#include <QObject>
#include <QString>
#include <QList>
using namespace std;
MC_talker::MC_talker()
    :db("dataski.txt")
{
    graph = new MC_graph();
}

void MC_talker::populate()
{
    MC_node *node;
    list<db_node> dbNodes = db.getDbNodes();
    for(db_node dbn:dbNodes)
    {
        node=new MC_node(dbn.id,dbn.name,dbn.altitude);
        graph->addNode(node);
        QObject::connect(node,SIGNAL(selectedSignal(int)),graphWidget,SLOT(electSignal(int)));
    }

    //MC_edge *edge;
    list<db_edge> dbEdges = db.getDbEdges();
    //ugly nested for ahead
    MC_node* mcnode_source=NULL;
    MC_node* mcnode_dest=NULL;
    for(db_edge dbe:dbEdges)
    {
        for(MC_node* mcnode:graph->listOfNodes)
            if(mcnode->id == dbe.idSourcePoint)
            {
                mcnode_source=mcnode;
                break;
            }
        for(MC_node* mcnode:graph->listOfNodes)
            if(mcnode->id == dbe.idDestPoint)
            {
                mcnode_dest=mcnode;
                break;
            }
        graph->connectNode(mcnode_source,mcnode_dest,dbe.id,dbe.name,dbe.tr);
        mcnode_source=NULL;
        mcnode_dest=NULL;
    }
    /*
    MC_node *node1=new MC_node(0,QString("ipsum").toStdString(),10000);

    graph->addNode(node1);

    QObject::connect(node1,SIGNAL(selectedSignal(int)),graphWidget,SLOT(electSignal(int)));

    graph->connectNode(node1,node2,1,"premier e",TypeRoute::V);
    */
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
    return string();
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

list<int> MC_talker::getReachableNodeWithCondition(int id,TypeRoute tr)
{
    list<MC_node *> listOfReachedNode;
    listOfReachedNode = graph->dfs(getNodeFromId(id),tr);

    list<int> listOfNodeId;
    for(MC_node *n:listOfReachedNode)
        listOfNodeId.push_back(n->id);
    return listOfNodeId;
}

void MC_talker::startShortestPath(int idFrom, int idTo)
{
    std::cout << "MC Talker : Dijsktra : from : " << idFrom << " to : " << idTo << std::endl;
    graph->dijkstra(getNodeFromId(idFrom),getNodeFromId(idTo));
}

void MC_talker::setGraphWidget(GraphWidget *graphW)
{
    graphWidget=graphW;
    QObject::connect(graph,SIGNAL(nodeCreated(int,string,int)),graphWidget,SLOT(createNode(int,string,int)));
    QObject::connect(graph,SIGNAL(edgeCreated(int,int,int,string,int,int,TypeRoute)),
         graphWidget,SLOT(createEdge(int,int,int,string,int,int,TypeRoute)));
}
