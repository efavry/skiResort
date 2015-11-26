#include "list"
#include "mc_talker.h"
#include "../view/node.h"
#include <QObject>
#include <QString>
#include <QList>
using namespace std;
MC_talker::MC_talker()
{
    graph = new MC_graph();
    /*for (int i=0; i<35 ; ++i)
    {
        graph->addNode(new MC_node(i,QString::number(i).append("test").toStdString(),10000));
        graph->connectNode(graph->listOfNodes[]);
    }*/


}

void MC_talker::populate()
{
    MC_node *node1=new MC_node(0,QString("ipsum node").toStdString(),10000);
    MC_node *node2=new MC_node(1,QString("quia node").toStdString(),500);
    MC_node *node3=new MC_node(2,QString("dolor node").toStdString(),1000);
    MC_node *node4=new MC_node(3,QString("sit node").toStdString(),400);
    MC_node *node5=new MC_node(4,QString("amet node").toStdString(),1050);
    MC_node *node6=new MC_node(5,QString("gauss node").toStdString(),2300);

    graph->addNode(node1);
    graph->addNode(node2);
    graph->addNode(node3);
    graph->addNode(node4);
    graph->addNode(node5);
    graph->addNode(node6);

    graph->connectNode(node1,node2,1,"premier e",TypeRoute::V);
    graph->connectNode(node2,node3,2,"second e",TypeRoute::B);
    graph->connectNode(node3,node4,3,"troisieme e",TypeRoute::TC);
    graph->connectNode(node4,node5,4,"quatrieme e",TypeRoute::N);
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

void MC_talker::setGraphWidget(GraphWidget *graphW)
{
    /*
    //qlist for qt and std list for stl

    V_Node* vn=NULL;
    for(MC_node* n: graph->listOfNodes)
    {
        if(vn==NULL)
        {
            vn = new V_Node(graphWidget,n->id,QString::fromStdString(n->name),true,true);
            graphWidget->addCenterNode(vn);
        }
        else
        {
            vn = new V_Node(graphWidget,n->id,QString::fromStdString(n->name));
            graphWidget->addNode(vn);
        }
    }

    for(MC_node* nToLink: graph->listOfNodes)
        foreach(V_Node* vnToLink,graphWidget->listOfNode)
            if(nToLink->id == vnToLink->id)
                for(MC_node* nToScan: nToLink->l_successors)
                    foreach(V_Node* vnToScan,graphWidget->listOfNode)
                        if(nToScan->id == vnToScan->id)
                            graphWidget->connectNode(vnToLink,vnToScan);*/
    graphWidget=graphW;
    QObject::connect(graph,SIGNAL(nodeCreated(int,string,int)),graphWidget,SLOT(createNode(int,string,int)));
    QObject::connect(graph,SIGNAL(edgeCreated(int,int,int,string,int,int,TypeRoute)),
         graphWidget,SLOT(createEdge(int,int,int,string,int,int,TypeRoute)));
}